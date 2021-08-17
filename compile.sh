g++ temp.cpp -std=c++17 -w -o foo
if ($? -ne 0) then
    echo "Compile failed!"
    exit 1
else
    exit 0
fi