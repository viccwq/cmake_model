#!/bin/sh
#referce:https://www.cnblogs.com/wangqiguo/p/7191352.html
SRC_FILE="../common/utility/vxlGitVersion.h.tmp"
DST_FILE="../common/utility/vxlGitVersion.h"

commit_ts=`git log -1 --format="%ct"`
commit_time=`date -d@$commit_ts +"%Y-%m-%d %H:%M:%S"`
current_time=`date +"%Y-%m-%d %H:%M:%S"`
git_version=`git log -1 --format="%h"`
git_author=`git log -1 --format="%ae"`
echo "commit_ts:   "${commit_ts}
echo "commit_time: "${commit_time}
echo "current_time:"${current_time}
echo "git_version: "${git_version}
echo "git_author:  "${git_author}

cp ${SRC_FILE} ${DST_FILE}
sed -i s/"GIT_VERSION"/"${git_version}"/g ${DST_FILE}
sed -i s/"GIT_AUTHOR"/"${git_author}"/g ${DST_FILE}
sed -i s/"GIT_CI_TIME"/"${commit_time}"/g ${DST_FILE}
sed -i s/"GIT_CR_TIME"/"${current_time}"/g ${DST_FILE}