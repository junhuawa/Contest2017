#!/bin/sh
#set -x

num=$1
echo "num: $num"

if [ "$num" = "5" ]; then

./test5 < ../testcase/Q5/bts_deployment_small_1497491702434 > ~/test.log
diff ~/test.log ../testcase/Q5/small_result.txt

./test5 < ../testcase/Q5/bts_deployment_large_1497491738779 > ~/large.log
diff ~/large.log ../testcase/Q5/large_result.txt
fi

if [ "$num" = "4" ]; then

./test4 < ../testcase/Q4/small_input_8.txt > ~/small.log

./test4 < ../testcase/Q4/large_input_7.txt > ~/large.log

diff ~/small.log ../testcase/Q4/small.log

diff ~/large.log ../testcase/Q4/large.log

fi

if [ "$num" = "3" ]; then

    sleep 1
fi

if [ "$num" = "2" ]; then
    sleep 1
fi

if [ "$num" = "1" ]; then
    sleep 1
fi
