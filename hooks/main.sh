#!/bin/bash

src_path="/usr/share/uos-installer/hooks"
chroot_path="/target"
work_path="/uos-installer"
user_settings_path="$work_path/installer_settings.json"
disk_settings_path="$work_path/parted.json"
packagelist_path="$work_path/package.list"
process_control_path="/tmp/uos-installer-process"

user_check(){  
    if [ "$USER" != "root" ];then
        echo "please use root user or sudo !"
        exit 3
    fi
}

copy_dir(){
    if [ ! -d $work_path ];then
        mkdir -p $work_path
    fi
    cp -rv $src_path/* $work_path
    chmod -R 777 $work_path
}

process_control(){
    echo "$1" > "$process_control_path"
}

main(){  
    
    DEVICE="$1"
    if [ ! -b "$DEVICE" ];then
        echo "device path error, please check"
        exit 2
    fi

    EFI=""
    if [[ -n $2 ]];then
        EFI="$2"
    fi

    user_check
    copy_dir
    

    cd  $work_path || exit
    cd ./auto-part/ || exit
    process_control "auto_part start_part"
    bash ./auto_part.sh "$DEVICE" "$disk_settings_path" "$EFI"
    process_control "auto_part mount_target"
    bash ./mount_target.sh "$DEVICE" "$disk_settings_path"
    cd ..


    bash ./before_chroot/before_chroot.sh
    process_control "before_chroot creat_fstab"
    bash ./auto-part/create_fstab.sh
    
    bash ./tools/mount_chroot.sh "$chroot_path"
    cp -rv ./in_chroot "$chroot_path"/$work_path
    cp -v $user_settings_path "$chroot_path"/$user_settings_path
    cp -v $packagelist_path "$chroot_path"/$packagelist_path
    chmod a+x "$chroot_path"/$work_path/*.sh
    process_control "in_chroot start"
    chroot "$chroot_path" /$work_path/in_chroot.sh "$DEVICE" "$EFI"

    echo "in_chroot end" > /target"$process_control_path"

    bash ./tools/umount_chroot.sh "$chroot_path"
    bash ./auto-part/umount_target.sh
    
}

main "$@"