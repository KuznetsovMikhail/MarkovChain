import re

with open('Source/Oxxxymiron.txt') as inf:
    text = inf.read()
    songs = re.findall(r'<.+>\n', text)
    with open('Source/OxxxymironClean.txt', 'a+', encoding='utf-8') as ouf:
        ouf.write(re.sub(r'<.+>\n', '', text))

print(*songs, sep='\n\n')

print(len(songs))
