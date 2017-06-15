#!/bin/sh
./test5 < ../testcase/Q5/bts_deployment_small_1497491702434 > ~/test.log
diff ~/test.log ../testcase/Q5/small_result.txt

./test5 < ../testcase/Q5/bts_deployment_large_1497491738779 > ~/large.log
diff ~/large.log ../testcase/Q5/large_result.txt
