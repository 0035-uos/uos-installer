#!/bin/bash
isomount_path=""
squashfs_path=""
work_path="/uos-installer/before_chroot/"

process_control(){
    echo "$1" > /tmp/uos-installer-process
}

if grep -q boot=casper /proc/cmdline; then
  BOOT=casper
  CDROM=/cdrom
  LUPIN_ROOT=/isodevice
  DISTRIBUTION=ubuntu
elif grep -q boot=live /proc/cmdline; then
  BOOT=live

  if [ -d /lib/live/mount/medium/live ]; then
    CDROM=/lib/live/mount/medium
  else
    CDROM=/run/live/medium
  fi

  LUPIN_ROOT=/lib/live/mount/findiso
  DISTRIBUTION=debian
else
  error "No boot value found!"
fi

if [[ -n $CDROM ]];then
    isomount_path=$CDROM
    squashfs_path=$CDROM/live/filesystem.squashfs
else
    isomount_path="/run/live/medium"
    squashfs_path=$CDROM/live/filesystem.squashfs
fi

if [ -f $CDROM/live/minios.img ];then
  squashfs_path=$CDROM/live/minios.img
fi

process_control "before_chroot start_unsquashfs"
bash $work_path/un_squashfs.sh $squashfs_path
process_control "before_chroot set_repo"
bash $work_path/set_repo.sh $isomount_path