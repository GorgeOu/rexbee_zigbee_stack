#!/bin/bash
echo "********************post build***********************" 
echo "para (1)$1 (2)$2 (3)$3"

today=$(date "+%Y%m%d")

dirname=$2/build/$3
if [ ! -d $dirname  ];then
  mkdir $dirname
fi
rm -rf $2/boot.link

os="$(uname -s)"

case "$os" in
  Linux)
    fw_check_tool="$2/tools/post_build_fw_check.out"
    toolchain_objcopy="$4/bin/tc32-elf-objcopy"
    toolchain_objdump="$4/bin/tc32-elf-objdump"
    ;;
  Darwin)
    echo "macOS"
    exit 0
    ;;
  CYGWIN*|MINGW*)
    fw_check_tool="$2/tools/post_build_fw_check.exe"
    toolchain_objcopy="tc32-elf-objcopy"
    toolchain_objdump="tc32-elf-objdump"
    ;;
  *)
    echo "Unknown system: $os"
    exit 1
    ;;
esac

print_usage_table() {
  local used_ramcode="$1"
  local remaining_ramcode=0
  local used_stack="$2"
  local remaining_stack=0
  local used_ret_ram="$3"
  local remaining_ret_ram="$4"
  local used_ram="$5"
  local remaining_ram="$6"
  local used_flash="$7"
  local remaining_flash="$8"

  local col_metric=10
  local col_used=12
  local col_remain=18

  printf '\n'

  printf '|-%*s-|-%*s-|-%*s-|\n' \
    $col_metric "$(printf '%.0s-' $(seq 1 $col_metric))" \
    $col_used   "$(printf '%.0s-' $(seq 1 $col_used))" \
    $col_remain "$(printf '%.0s-' $(seq 1 $col_remain))"
    
  printf '| %-*s | %*s | %*s |\n' \
    $col_metric Metric $col_used Used\(Bytes\) $col_remain Remaining\(Bytes\)

  printf '|-%*s-|-%*s-|-%*s-|\n' \
    $col_metric "$(printf '%.0s-' $(seq 1 $col_metric))" \
    $col_used   "$(printf '%.0s-' $(seq 1 $col_used))" \
    $col_remain "$(printf '%.0s-' $(seq 1 $col_remain))"

  printf '| %-*s | %*d | %*d |\n' \
    $col_metric RAMCODE $col_used $used_ramcode $col_remain $remaining_ramcode

  printf '| %-*s | %*d | %*d |\n' \
    $col_metric STACK $col_used $used_stack $col_remain $remaining_stack
  
  printf '| %-*s | %*d | %*d |\n' \
    $col_metric RAM\(RET\) $col_used $used_ret_ram $col_remain $remaining_ret_ram
    
  printf '| %-*s | %*d | %*d |\n' \
    $col_metric RAM $col_used $used_ram $col_remain $remaining_ram

  printf '| %-*s | %*d | %*d |\n' \
    $col_metric Flash $col_used $used_flash $col_remain $remaining_flash
  
  printf '|-%*s-|-%*s-|-%*s-|\n' \
    $col_metric "$(printf '%.0s-' $(seq 1 $col_metric))" \
    $col_used   "$(printf '%.0s-' $(seq 1 $col_used))" \
    $col_remain "$(printf '%.0s-' $(seq 1 $col_remain))"
  
  printf '\n'
}
${toolchain_objcopy} -v -O binary $3.elf  $dirname/$1[$today].bin

${fw_check_tool} $dirname/$1[$today].bin
${toolchain_objdump} -x -D -l -S $3.elf  > $dirname/$1[$today].lst
echo "generate .lst file done : $1[$today].lst"

ramcode_address_hex=$(grep '00000000 _ramcode_size_align_256_' "$dirname/$1[$today].lst" | awk '{print $1}')

# if not found, warn and exit
if [ -z "$ramcode_address_hex" ]; then
  	echo "Error: ramcode symbol not found in .lst file"
else	
	ramcode_size=$((16#$ramcode_address_hex+16#900))
	remaining_ramcode_size=0
fi

ret_address_hex=$(grep '00000000 _end_bss_' "$dirname/$1[$today].lst" | awk '{print $1}')

# if not found, warn and exit
if [ -z "$ret_address_hex" ]; then
  	echo "Error: ._end_bss_ symbol not found in .lst file"
else
	total_ret_mem=16#848000
	
	ret_address=$((16#$ret_address_hex))
	
	# compute available memory
	ret_available=$((total_ret_mem-ret_address))
	if (( ret_available < 0 )); then
	  ret_available=0
	fi
	
	used_ret_ram=$((ret_address - 16#840000 - $ramcode_size ))
fi

address_hex=$(grep '00000000 _end_no_zero_bss_' "$dirname/$1[$today].lst" | awk '{print $1}')
stack_address_hex=$(grep '00000000 _stack_end_' "$dirname/$1[$today].lst" | awk '{print $1}')

# if not found, warn and exit
if [ -z "$address_hex" ]; then
  	echo "Error: ._end_no_zero_bss_ symbol not found in .lst file"
else
	total_mem=16#850000
		
	stack_size=$(( 16#$stack_address_hex - 16#$address_hex ))
	
	address=$((16#$address_hex))
	
	# compute available memory
	remaining_ram=$(( total_mem - stack_size - address ))

	used_ram=$(( address - ret_address ))
fi

bin_file="$dirname/$1[$today].bin"

if [ ! -f "$bin_file" ]; then
	echo "Error: binary file not found: $bin_file"
else
	file_size=$(stat -c%s "$bin_file")
	
	max_app_size=237500 # 232KB - 4B - 64B 
	remaining_flash=$(( max_app_size - file_size ))
fi

print_usage_table "$ramcode_size" "$stack_size" "$used_ret_ram" "$ret_available" "$used_ram" "$remaining_ram" "$file_size" "$remaining_flash"

if (( remaining_flash < 0 )); then
	echo "Error: Firmware size exceeds OTA size limit; this firmware cannot be OTA updated."
	remaining_flash=0
fi

echo "**************** end of post build ******************"