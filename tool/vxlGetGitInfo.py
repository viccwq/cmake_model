#!/usr/bin/env python 
#coding:utf8 
import math,os,sys,csv
import subprocess,datetime
import shutil
from vxlLoadCfg import VXL_CFG,VXL_OS
 
SRC_FILE = os.getcwd() + "/../common/utility/vxlGitVersion.h.tmp" 
DST_FILE = os.getcwd() + "/../common/utility/vxlGitVersion.h" 
CFG_FILE = os.getcwd() + "/vxlCfg.csv"

#specify a file, replace all the "old_text" with "new_text"
def replace(old_text, new_text, file_name):
    #duplicate a new file which save the modificaiton
    file_name_new = ('%s.bak'%file_name)

    f = open(file_name, 'r')    
    f_new = open(file_name_new,'w')    
    for line in f.readlines():    
        f_new.write(line.replace(old_text, new_text))    
    f.close()    
    f_new.close()
    #remove the duplicated file
    shutil.copy(file_name_new, file_name)
    os.remove(file_name_new)
    return

def parse_version(ver_str):
    #default version number
    ver_dst = ['0', '0', '0', '0']

    #split the version string by '.'
    ver_str  = ver_str.strip()
    if len(ver_str) > 0:
        ver_src = ver_str.split('.')
    else:
        return ver_dst[0], ver_dst[1], ver_dst[2], ver_dst[3]

    #choose the last 4 version number
    for i, j in zip(range(len(ver_src)-1, -1, -1), range(len(ver_dst)-1, -1, -1)):
        print(i, j)
        ver_src[i] = (re.sub('\D','', ver_src[i]))
        if len(ver_src[i]) > 0:
            ver_dst[j] = ver_src[i]

    return ver_dst[0], ver_dst[1], ver_dst[2], ver_dst[3]

if __name__ == '__main__':
    #get info of system 
    if "win32" == sys.platform:
        sys_env = VXL_OS.OS_WINDOWS
    else:
        sys_env = VXL_OS.OS_LINUX
    #load configuration 
    vxl_config = VXL_CFG(sys_env)
    dict_tmp = vxl_config.load_cfg(CFG_FILE)
    print(dict_tmp)

    #check the existance of exe
    git_exe = vxl_config.git_path + '/git.exe'
    if not os.path.exists(git_exe):
        exit("ERROR: can not find git.exe in system!")

    #init variable
    git_ci_ts   = ""
    git_cr_time = ""
    git_ci_time = ""
    git_version = ""
    git_author  = ""
    git_cr_tag  = ""

    ver_status  = "R"
    ver_major   = "0"
    ver_minor   = "0"
    ver_patch   = "0"
    ver_revision= "0"

    #get git information
    if "win32" == sys.platform:
        git_ci_ts   = subprocess.getoutput('"' + git_exe + '"' + ' log -1 --format="%ct"')
        git_cr_time = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        git_ci_time = subprocess.getoutput('"' + git_exe + '"' + ' log -1 --format="%cd" --date=format:"%Y-%m-%d %H:%M:%S"')
        git_version = subprocess.getoutput('"' + git_exe + '"' + ' log -1 --format="%h"')
        git_author  = subprocess.getoutput('"' + git_exe + '"' + ' log -1 --format="%ae"')
        git_cr_tag  = subprocess.getoutput('"' + git_exe + '"' + ' tag --points-at ' + git_version)
        #git_cr_tag  = subprocess.getoutput('"' + git_exe + '"' + ' tag --points-at HEAD^^')
    else:
        git_ci_ts   = ""
        git_cr_time = ""
        git_ci_time = ""
        git_version = ""
        git_author  = ""
        git_cr_tag  = ""
    
    (ver_major, ver_minor, ver_patch, ver_revision) = parse_version(git_cr_tag)
    #generate head file
    SRC_FILE_TMP = SRC_FILE+".tmp"
    shutil.copy(SRC_FILE, SRC_FILE_TMP)
    replace("GIT_VERSION", git_version, SRC_FILE_TMP)
    replace("GIT_AUTHOR",  git_author,  SRC_FILE_TMP)
    replace("GIT_CI_TIME", git_ci_time, SRC_FILE_TMP)
    replace("GIT_CR_TIME", git_cr_time, SRC_FILE_TMP)
    replace("GIT_CR_TAG",  git_cr_tag,  SRC_FILE_TMP)
    replace("GIT_VER_STATS", ver_status,  SRC_FILE_TMP)
    replace("GIT_VER_MAJOR", ver_major,   SRC_FILE_TMP)
    replace("GIT_VER_MINOR", ver_minor,   SRC_FILE_TMP)
    replace("GIT_VER_PATCH", ver_patch,   SRC_FILE_TMP)
    replace("GIT_VER_REVIS", ver_revision,SRC_FILE_TMP)
    shutil.copy(SRC_FILE_TMP, DST_FILE)
    os.remove(SRC_FILE_TMP)
