g++ temp.cpp -std=c++17 -w -o foo && rm foo
if [ $? -ne 0 ] 
then
    echo "Compile failed!"
    exit 1
else
    exit 0
fi
done