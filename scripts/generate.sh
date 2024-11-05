rm -rf tmp
mkdir -p tmp
frequency dist/passwd 100 > tmp/substr.txt
./scripts/sort_and_remove.sh tmp/substr.txt
head -n 1000 tmp/substr.txt > tmp/substr.txt.tmp
mv tmp/substr.txt.tmp tmp/substr.txt

python src/utils/keyboard.py dist/passwd 20 > tmp/KA.txt
./scripts/sort_and_remove.sh tmp/KA.txt
head -n 1000 tmp/KA.txt > tmp/KA.txt.tmp
mv tmp/KA.txt.tmp tmp/KA.txt

pinyin pinyins ./dist/passwd 10 > tmp/word1.txt
./scripts/sort_and_remove.sh tmp/word1.txt
head -n 1000 tmp/word1.txt > tmp/word1.txt.tmp
mv tmp/word1.txt.tmp  tmp/word1.txt

./scripts/append.sh ./tmp/word1.txt ./tmp/word1.txt > ./tmp/word2.txt
pinyin ./tmp/word2.txt ./dist/passwd 5 > tmp/word2.txt.tmp
mv tmp/word2.txt.tmp tmp/word2.txt
./scripts/sort_and_remove.sh tmp/word2.txt
head -n 1000 tmp/word2.txt > tmp/word2.txt.tmp
mv tmp/word2.txt.tmp tmp/word2.txt

./scripts/append.sh ./tmp/word2.txt ./tmp/word1.txt > ./tmp/word3.txt
pinyin ./tmp/word3.txt ./dist/passwd 5 > tmp/word3.txt.tmp
mv tmp/word3.txt.tmp tmp/word3.txt
./scripts/sort_and_remove.sh tmp/word3.txt
head -n 1000 tmp/word3.txt > tmp/word3.txt.tmp
mv tmp/word3.txt.tmp tmp/word3.txt

cat tmp/word1.txt > tmp/words.txt
cat tmp/word2.txt >> tmp/words.txt
cat tmp/word3.txt >> tmp/words.txt

#./scripts/arange.sh tmp/words.txt tmp/KA.txt tmp/substr.txt > wordlist.txt
permutation tmp/words.txt tmp/KA.txt tmp/substr.txt > wordlist.txt
