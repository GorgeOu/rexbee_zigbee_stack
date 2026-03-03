# Rexense Zigbee Stack SDK — 架构文档

> 本文档描述 SDK 的**生命周期**、**时序逻辑**及**调用关系图谱**。  
> 图表使用 [Mermaid](https://mermaid.js.org/) 语法，可在 GitHub / VS Code 等环境直接渲染。

---

## 目录

1. [SDK 生命周期](#1-sdk-生命周期)
   - [1.1 系统启动（Cold Boot）流程](#11-系统启动cold-boot流程)
   - [1.2 睡眠 / 唤醒（End Device）流程](#12-睡眠--唤醒end-device流程)
   - [1.3 主循环（Main Loop）流程](#13-主循环main-loop流程)
2. [时序逻辑（Sequence Diagrams）](#2-时序逻辑sequence-diagrams)
   - [2.1 入网流程（Network Join）](#21-入网流程network-join)
   - [2.2 消息接收处理流程](#22-消息接收处理流程)
   - [2.3 消息发送流程](#23-消息发送流程)
   - [2.4 OTA 升级流程](#24-ota-升级流程)
3. [调用关系图谱（Module Dependency）](#3-调用关系图谱module-dependency)
   - [3.1 模块总览](#31-模块总览)
   - [3.2 回调函数（Weak Function）关系图](#32-回调函数weak-function关系图)
   - [3.3 插件注册关系图](#33-插件注册关系图)

---

## 1. SDK 生命周期

### 1.1 系统启动（Cold Boot）流程

设备上电后，SDK 按照以下顺序依次调用用户可重写的 **weak callback**，完成硬件初始化、协议栈配置、插件注册及应用入口。

```mermaid
flowchart TD
    POR["上电 / 复位 (Power-On Reset)"] --> A["app_general_pre_hal_config()"]
    A --> B["内部 HAL 初始化 (Radio / Timer / IRQ)"]
    B --> C["app_hal_uart_config()"]
    C --> D["app_hal_config()"]
    D --> E["SimEEPROM / NVM 初始化"]
    E --> F["app_get_token_data_to_ram_callback()"]
    F --> G["app_post_token_init_callback()"]
    G -->|"注册 NVM 用户 Token"| H["stack_key_parameter_configuration()"]
    H -->|"设置 PAN ID / Channel / TX Power 等"| I["协议栈内存分配 & 网络初始化"]
    I --> J["app_post_endpoint_config_callback()"]
    J --> K["Cluster / Attribute 表初始化"]
    K --> L["app_plugin_init_callback()"]
    L -->|"注册 Button / OTA / Reporting 等插件"| M["app_main_init_callback()"]
    M --> N["进入主循环 (Main Loop)"]

    style POR fill:#f96,stroke:#333,color:#fff
    style N fill:#6c6,stroke:#333,color:#fff
```

### 1.2 睡眠 / 唤醒（End Device）流程

End Device 支持深度睡眠以节省功耗。唤醒后走简化的初始化路径。

```mermaid
flowchart TD
    SLEEP["设备进入睡眠 (Deep Sleep)"] --> WAKE["外部中断 / 定时器唤醒"]
    WAKE --> A2["app_general_pre_hal_config()"]
    A2 --> B2["app_hal_uart_config()"]
    B2 --> C2["app_hal_config()"]
    C2 --> D2["sleep_wakeup_callback()"]
    D2 --> E2{"外部唤醒触发?"}
    E2 -->|"是"| F2["app_keep_wakeup_ext_trigger_callback()"]
    E2 -->|"否"| G2["app_ok_to_sleep_callback()"]
    F2 --> H2["恢复主循环 (Main Loop)"]
    G2 -->|"允许再次睡眠"| SLEEP
    G2 -->|"不允许"| H2

    style SLEEP fill:#669,stroke:#333,color:#fff
    style WAKE fill:#f96,stroke:#333,color:#fff
```

### 1.3 主循环（Main Loop）流程

进入主循环后，SDK 以事件驱动方式周期调用用户 Tick 回调和内部协议栈任务。

```mermaid
flowchart TD
    LOOP["Main Loop 入口"] --> T1["协议栈内部 Tick (MAC / NWK / APS)"]
    T1 --> T2["app_main_tick_callback()"]
    T2 --> T3["app_second_tick_callback() (每秒)"]
    T3 --> T4["事件调度器 (Event Scheduler)"]
    T4 --> T5["LED 任务调度"]
    T5 --> T6["Button 扫描"]
    T6 --> T7{"有待处理消息?"}
    T7 -->|"是"| T8["消息处理流程"]
    T7 -->|"否"| T9{"End Device?"}
    T8 --> T9
    T9 -->|"是"| T10{"app_ok_to_sleep_callback()"}
    T9 -->|"否"| LOOP
    T10 -->|"允许睡眠"| SLEEP["进入睡眠"]
    T10 -->|"不允许"| LOOP

    style LOOP fill:#6c6,stroke:#333,color:#fff
```

---

## 2. 时序逻辑（Sequence Diagrams）

### 2.1 入网流程（Network Join）

```mermaid
sequenceDiagram
    participant App as 应用层
    participant SDK as Zigbee Stack SDK
    participant NWK as 网络层
    participant Coord as Coordinator

    App->>SDK: app_scan_network_v3_start(channel_mask, duration)
    SDK->>App: app_scan_network_process_init_callback()
    
    loop 每 500ms
        SDK->>App: app_scan_network_process_indicate(attempt)
    end

    SDK->>NWK: 发送 Beacon Request
    NWK->>Coord: Beacon Request (广播)
    Coord-->>NWK: Beacon Response
    NWK->>SDK: Beacon 解析 & 选择最佳父节点
    SDK->>NWK: Association Request
    NWK->>Coord: Association Request
    Coord-->>NWK: Association Response (网络地址)
    NWK->>SDK: 入网成功

    SDK->>App: app_stack_status_callback(NETWORK_UP)
    SDK->>App: app_integrated_network_state_changed_callback()
    SDK->>App: app_scan_network_process_joined_callback()
    SDK->>App: app_device_fresh_start_callback()
    SDK->>App: app_device_network_start_callback()

    Note over App: 可在此启动 Reporting 等业务
```

### 2.2 消息接收处理流程

```mermaid
sequenceDiagram
    participant Radio as 射频层
    participant SDK as Zigbee Stack SDK
    participant App as 应用层

    Radio->>SDK: 收到无线帧
    SDK->>SDK: MAC / NWK / APS 解包
    SDK->>App: app_pre_message_handler(type, message)
    
    alt ZDO 消息
        SDK->>App: app_pre_zdo_handler(clusterId, message)
        App-->>SDK: handled / not-handled
    else ZCL 消息
        SDK->>App: app_pre_command_handler(cmd)
        App-->>SDK: handled / not-handled
        
        alt 应用未处理 → 内置插件处理
            SDK->>SDK: 内置 Plugin 处理 (OnOff / Level / Color ...)
        else 插件未处理
            alt Client-to-Server
                SDK->>App: app_cluster_specific_c2s_command_parse()
            else Server-to-Client
                SDK->>App: app_cluster_specific_s2c_command_parse()
            end
        end
    end

    SDK->>App: app_post_attr_change_handler(endpoint, clusterId, attrId)
    Note over App: 属性变更后回调
```

### 2.3 消息发送流程

```mermaid
sequenceDiagram
    participant App as 应用层
    participant Queue as 消息队列
    participant SDK as Zigbee Stack SDK
    participant Radio as 射频层

    App->>Queue: app_uart_message_queue_send(header, delivery, fmt, ...)
    Queue->>SDK: 填充 ZCL 帧 & 入队
    SDK->>App: app_pre_message_send_callback(header)
    SDK->>Radio: MAC 层发送
    Radio-->>SDK: ACK / NACK
    SDK->>App: app_message_sent_callback(status, indexOrDestination)
    
    alt 发送失败 & 开启重试
        SDK->>Radio: 重试发送
    end
```

### 2.4 OTA 升级流程

```mermaid
sequenceDiagram
    participant Server as OTA Server
    participant SDK as Zigbee Stack SDK
    participant App as 应用层

    Server->>SDK: OTA Image Notify
    SDK->>Server: Query Next Image Request
    Server-->>SDK: Query Next Image Response
    
    loop 分块下载
        SDK->>Server: Image Block Request
        Server-->>SDK: Image Block Response
        SDK->>SDK: 写入 Flash
    end
    
    SDK->>SDK: 镜像校验 (CRC / Signature)
    SDK->>App: OTA 完成回调
    SDK->>SDK: 系统重启 & Bootloader 切换镜像
```

---

## 3. 调用关系图谱（Module Dependency）

### 3.1 模块总览

```mermaid
graph TB
    subgraph 应用层["应用层 (Application)"]
        APP["用户回调实现<br/>(Callbacks .c)"]
        CFG["设备配置<br/>(app_common.h)"]
    end

    subgraph SDK层["SDK 核心层"]
        INIT["初始化管理器"]
        EVENT["事件调度器"]
        MSG["消息处理器"]
        ATTR["属性服务器<br/>(Attribute Server)"]
        PLUGIN["插件管理器"]
    end

    subgraph 插件层["内置插件 (Plugins)"]
        P_ONOFF["OnOff Plugin"]
        P_LEVEL["Level Plugin"]
        P_COLOR["Color Plugin"]
        P_SCENE["Scene Plugin"]
        P_OTA["OTA Client Plugin"]
        P_RPT["Reporting Plugin"]
        P_BTN["Button Plugin"]
        P_BAT["Battery Plugin"]
        P_IAS["IAS Zone Plugin"]
        P_POLL["Poll Control Plugin"]
    end

    subgraph 网络层["网络层 (Network)"]
        NWK["NWK 管理<br/>(global_nwk_mgmt_apis)"]
        BIND["绑定管理<br/>(global_binding_mgmt_apis)"]
        GRP["组 & 场景<br/>(global_group_scene_apis)"]
        ZLL["ZLL 触摸链接<br/>(global_zll_apis)"]
        FAST["快速入网<br/>(fast_join_apis)"]
    end

    subgraph HAL层["硬件抽象层 (HAL)"]
        GPIO["GPIO / PWM / ADC"]
        UART["UART / SPI / I2C"]
        FLASH["Flash / NVM"]
        LED["LED 任务"]
        TIMER["Timer / Event"]
    end

    APP --> INIT
    APP --> EVENT
    APP --> MSG
    APP --> PLUGIN
    CFG --> ATTR

    INIT --> NWK
    MSG --> ATTR
    PLUGIN --> P_ONOFF & P_LEVEL & P_COLOR & P_SCENE
    PLUGIN --> P_OTA & P_RPT & P_BTN & P_BAT & P_IAS & P_POLL

    P_ONOFF & P_LEVEL & P_COLOR --> ATTR
    P_RPT --> MSG
    P_OTA --> MSG
    P_BTN --> GPIO
    P_BAT --> GPIO
    P_POLL --> NWK

    NWK --> HAL层
    MSG --> NWK
    BIND --> NWK
    GRP --> NWK
    ATTR --> FLASH

    style 应用层 fill:#e8f5e9,stroke:#2e7d32
    style SDK层 fill:#e3f2fd,stroke:#1565c0
    style 插件层 fill:#fff3e0,stroke:#e65100
    style 网络层 fill:#f3e5f5,stroke:#6a1b9a
    style HAL层 fill:#fce4ec,stroke:#b71c1c
```

### 3.2 回调函数（Weak Function）关系图

所有用户回调均以 `__attribute__((weak))` 声明于 `weak_function.c`，应用程序按需覆盖。

```mermaid
graph LR
    subgraph 生命周期回调["生命周期回调"]
        CB1["app_general_pre_hal_config()"]
        CB2["app_hal_uart_config()"]
        CB3["app_hal_config()"]
        CB4["app_get_token_data_to_ram_callback()"]
        CB5["app_post_token_init_callback()"]
        CB6["stack_key_parameter_configuration()"]
        CB7["app_post_endpoint_config_callback()"]
        CB8["app_plugin_init_callback()"]
        CB9["app_main_init_callback()"]
        CB10["app_main_tick_callback()"]
    end

    subgraph 网络回调["网络状态回调"]
        NC1["app_stack_status_callback()"]
        NC2["app_device_fresh_start_callback()"]
        NC3["app_device_rejoin_successful_callback()"]
        NC4["app_device_network_start_callback()"]
        NC5["app_device_network_leaved_callback()"]
        NC6["app_leave_network_detected_callback()"]
    end

    subgraph 入网扫描回调["入网扫描回调"]
        SC1["app_scan_network_process_init_callback()"]
        SC2["app_scan_network_process_indicate()"]
        SC3["app_scan_network_process_joined_callback()"]
        SC4["app_scan_network_process_timeout_callback()"]
    end

    subgraph 消息回调["消息处理回调"]
        MC1["app_pre_message_handler()"]
        MC2["app_pre_zdo_handler()"]
        MC3["app_pre_command_handler()"]
        MC4["app_post_attr_change_handler()"]
        MC5["app_pre_message_send_callback()"]
        MC6["app_message_sent_callback()"]
        MC7["app_cluster_specific_c2s_command_parse()"]
        MC8["app_cluster_specific_s2c_command_parse()"]
    end

    subgraph 外设回调["外设 & 输入回调"]
        IC1["app_io_press_callback()"]
        IC2["app_io_release_callback()"]
        IC3["app_contact_changed_callback()"]
        IC4["app_process_uart_data()"]
    end

    subgraph 睡眠回调["睡眠管理回调"]
        SL1["sleep_wakeup_callback()"]
        SL2["app_ok_to_sleep_callback()"]
        SL3["app_keep_wakeup_ext_trigger_callback()"]
    end

    subgraph Lighting回调["灯控插件回调"]
        LC1["app_onoff_plugin_onoff_status_callback()"]
        LC2["app_level_plugin_level_change_start/stop()"]
        LC3["app_color_plugin_*_start/stop()"]
    end

    CB1 --> CB2 --> CB3 --> CB4 --> CB5 --> CB6 --> CB7 --> CB8 --> CB9 --> CB10

    style 生命周期回调 fill:#e8f5e9,stroke:#2e7d32
    style 网络回调 fill:#e3f2fd,stroke:#1565c0
    style 入网扫描回调 fill:#f3e5f5,stroke:#6a1b9a
    style 消息回调 fill:#fff3e0,stroke:#e65100
    style 外设回调 fill:#fce4ec,stroke:#b71c1c
    style 睡眠回调 fill:#e0f7fa,stroke:#00695c
    style Lighting回调 fill:#fff9c4,stroke:#f57f17
```

### 3.3 插件注册关系图

插件在 `app_plugin_init_callback()` 中注册，各插件通过属性服务器和消息处理器与协议栈交互。

```mermaid
graph TD
    INIT["app_plugin_init_callback()"]

    INIT --> BTN["app_button_plugin_v2_register()<br/>按键插件"]
    INIT --> OTA["app_ota_client_plugin_register()<br/>OTA 升级插件"]
    INIT --> RPT["app_reporting_plugin_reporting_config_register()<br/>上报插件"]
    INIT --> IAS["app_ias_zone_plugin_register()<br/>IAS Zone 插件"]
    INIT --> BAT["app_battery_monitor_plugin_register()<br/>电池监测插件"]
    INIT --> SCENE["app_scene_plugin_v2_register()<br/>场景插件"]
    INIT --> POLL["app_poll_control_server_plugin_register()<br/>Poll 控制插件"]
    INIT --> MT["app_mass_production_test_register()<br/>量产测试插件"]
    INIT --> LOCK["Door Lock Plugin"]
    INIT --> WC["Window Covering Plugin"]

    BTN --> |"按下/释放回调"| APP_CB["应用回调"]
    OTA --> |"OTA 状态回调"| APP_CB
    RPT --> |"上报结果回调"| APP_CB
    IAS --> |"Zone 状态变更"| APP_CB
    BAT --> |"低电量回调"| APP_CB
    POLL --> |"Poll 结果回调"| APP_CB

    style INIT fill:#e3f2fd,stroke:#1565c0
    style APP_CB fill:#e8f5e9,stroke:#2e7d32
```

---

## 附录：典型应用开发流程

以下展示一个 Router 设备从创建到入网的典型开发步骤：

```mermaid
flowchart LR
    A["1. 定义 app_common.h<br/>(Endpoint / Cluster / Attribute)"] --> B["2. 实现 stack_key_parameter_configuration()<br/>(PAN ID / Channel / TX Power)"]
    B --> C["3. 实现 app_plugin_init_callback()<br/>(注册所需插件)"]
    C --> D["4. 实现 app_main_init_callback()<br/>(启动入网扫描)"]
    D --> E["5. 实现 app_device_network_start_callback()<br/>(入网后业务启动)"]
    E --> F["6. 实现消息回调<br/>(处理 ZCL 命令)"]
    F --> G["7. 实现 app_main_tick_callback()<br/>(周期任务)"]
```

---

## 附录：API 头文件索引

| 头文件 | 功能模块 | 关键 API |
|--------|---------|----------|
| `global_apis.h` | 总入口 | 包含所有子模块头文件 |
| `global_common.h` | 通用定义 | 设备信息、事件注册、调试接口 |
| `global_nwk_mgmt_apis.h` | 网络管理 | `app_scan_network_v3_start()`, `app_leave_network()`, `app_get_network_state()` |
| `global_message_apis.h` | 消息收发 | ZCL/ZDO 消息构造与发送 |
| `global_binding_mgmt_apis.h` | 绑定管理 | 绑定表操作 |
| `global_group_scene_apis.h` | 组 & 场景 | 组管理、场景存储与恢复 |
| `global_button_apis.h` | 按键管理 | 按键事件注册、多击检测 |
| `global_hal_common_apis.h` | 硬件抽象 | GPIO / PWM / ADC / Flash / SPI / I2C |
| `global_lighting_apis.h` | 灯控驱动 | 色温、RGB、PWM 渐变 |
| `global_mem_heap_apis.h` | 动态内存 | Heap malloc / free |
| `global_nvm_apis.h` | NVM 存储 | Token 持久化、NVM3 |
| `global_zll_apis.h` | ZLL 触摸链接 | Initiator / Target 配网 |
| `global_mass_production_test_apis.h` | 量产测试 | 被动/主动测试模式 |
| `fast_join_apis.h` | 快速入网 | Fast Join V3 |
| `global_string_util_apis.h` | 字符串工具 | Hex/ASCII 转换、MD5 |
