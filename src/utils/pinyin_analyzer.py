from pypinyin import pinyin, Style
import jieba

def pinyin_to_hanzi(pinyin_str):
    # 将拼音字符串分割成单个拼音
    pinyin_list = pinyin_str.split()
    # 生成可能的汉字列表
    hanzi_candidates = [jieba.lcut("".join([char for char in pinyin(p, style=Style.NORMAL, heteronym=True)[0]])) for p in pinyin_list]
    # 选择每组拼音的第一个汉字，这里可以根据实际情况优化选择逻辑
    chosen_hanzi = [candidates[0][0] for candidates in hanzi_candidates]
    return "".join(chosen_hanzi)


if __name__ == "__main__":
    print(pinyin_to_hanzi("ni hao"))
    pass
