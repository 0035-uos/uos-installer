#!/bin/bash
echo "=========================in_chroot==================================="
DEVICE="$1"
work_path="/uos-installer"
conf_path="$work_path/installer_settings.json"

EFI=""
if [[ -n $2 ]];then
    EFI=$2
fi

process_control(){
    echo "$1" > /tmp/uos-installer-process
}

process_control "in_chroot instatll_package"
bash $work_path/install_package.sh
process_control "in_chroot setup_bootloader"
bash $work_path/setup_bootloader.sh "$DEVICE" "$EFI"

process_control "user_setting setup_user"
bash $work_path/setup_user.sh $conf_path

process_control "user_setting setup_locale"
bash $work_path/setup_locale.sh $conf_path

process_control "user_setting setup_timezone"
bash $work_path/setup_timezone.sh $conf_path

process_control "user_setting setup_keyboard"
bash $work_path/setup_keyboard.sh $conf_path

process_control "user_setting setup_lightdm"
bash $work_path/setup_lightdm.sh