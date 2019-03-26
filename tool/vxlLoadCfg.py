#!/usr/bin/env python
#coding:utf8
import math,os,sys,csv
from enum import Enum

class VXL_OS(Enum):
    OS_RESERVE = 0
    OS_WINDOWS = 1
    OS_LINUX   = 2
    OS_UNIX    = 3

class VXL_CFG(object):
    """docstring for vxl configuration"""
    def __init__(self, os=VXL_OS.OS_UNIX):
        self.os = os
        self.file_name  = ""
        self.trunk_path = ""
        #variable loaded from csv file
        self.git_path  = ""
        self.test_val1 = ""
        self.test_val2 = ""
        return

    def load_cfg(self, file_name, trunk_path="./../"):

        self.file_name  = file_name
        self.trunk_path = trunk_path

        dict_cfg={}

        with open(self.file_name, newline='') as f:
            reader = csv.DictReader(f)
            for row in reader:
                key = row.get("VALS")
                value="0"
                if VXL_OS.OS_WINDOWS == self.os:
                    value = row.get("WINDOWS")
                elif VXL_OS.OS_LINUX == self.os:
                    value = row.get("LINUX")
                elif VXL_OS.OS_UNIX == self.os:
                    value = row.get("UNIX")
                else:
                    value = "-1"
                dict_cfg.update({key:value})        

        self.git_path  = dict_cfg.get("GIT_PATH")
        self.test_val1 = dict_cfg.get("TEST_VAL1")
        self.test_val2 = dict_cfg.get("TEST_VAL2")

        return dict_cfg

if __name__ == '__main__':
    my_config = VXL_CFG(VXL_OS.OS_WINDOWS)
    dict_cfg = my_config.load_cfg("./vxlCfg.csv")
    print(dict_cfg)