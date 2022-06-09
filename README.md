## Build the StringFilter
```
mkdir build
cd build
cmake ..
make
```

## Run
```
cd ..
./StringFilter  --filepath "file path of the word list" --pattern "the word that is being searched"
```

## Test
First, you may generate the word list for test running this script
```
# We want here to generate 200 words of 8 length and 4 different characters maximum!
./randstr.py -n 4 -l 8 -w 200
```
And therefore, you can use the file words.txt generate in the resources folder, and running the following command to search "Aa" for example
```
cd ..
./StringFilter  --filepath resources/words.txt --pattern "Aa"
```
