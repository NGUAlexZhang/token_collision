import jieba
from pypinyin import pinyin, Style, lazy_pinyin

def pinyin_to_hanzi(pinyin_str):
    # 将拼音字符串分割成单个拼音
    pinyin_list = pinyin_str.split()
    # 生成可能的汉字列表
    hanzi_candidates = [jieba.lcut("".join([char for char in pinyin(p, style=Style.NORMAL, heteronym=True)[0]])) for p in pinyin_list]
    # 选择每组拼音的第一个汉字，这里可以根据实际情况优化选择逻辑
    chosen_hanzi = [candidates[0][0] for candidates in hanzi_candidates]
    return "".join(chosen_hanzi)

# 示例使用
pinyin_input = "ni hao ma"
hanzi_output = pinyin_to_hanzi(pinyin_input)
print(hanzi_output)
hanzi = "测试"
print(lazy_pinyin(hanzi))
