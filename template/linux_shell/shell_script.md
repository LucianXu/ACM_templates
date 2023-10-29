# Formater.sh

修改 .out 以及 .ans 的格式:

1. 每一行行末删除空格,
2. 最后一行行末增加换行符.

```shell
#!/bin/bash

if false; then
    if [ ! -f "$1" ]; then
        echo "File not found!"
        exit 1
    fi
fi
# The code above is to ensure the stability of the program

sed -i 's/[[:space:]]*$//' "$1"
sed -i -e '${/^$/!G;}' "$1"
```

# md5er.sh

得到一份 cpp 代码的 MD5 码.

```shell
#!/bin/bash

hash=$(md5sum <(tr -d '[:space:]' < "$1") | awk '{print $1}')
echo "$hash"
```

# checker.sh

对一份代码跑所有测试样例并比对.

```shell
#!/bin/bash

# current=$(pwd)
cd "$1"

g++ -o main -O2 -std=c++17 -DLOCAL main.cpp

for input in *.in; do
    output=${input%.*}.out
    answer=${input%.*}.ans

    ./main < $input > $output

    echo "case ${input%.*}: "
    echo "My: "
    cat $output
    echo "Answer: "
    cat $answer

    # if you want to check by yourself, then you don't need the code below
    if false; then
        $("$current"/formater.sh $output)
        $("$current"/formater.sh $answer)

        if diff $output $answer > /dev/null; then
            echo "${input%.*}: Accepted"
        else
            echo "${input%.*}: Wrong answer"
    	cat $output
    	cat $answer
        fi
    fi
done
```
