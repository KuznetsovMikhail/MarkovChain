# получение названий альбомов

import re

with open('alboum_names.txt') as inf:
    text = inf.read()
    albums = re.findall(r'https://genius.com/albums/Oxxxymiron/[a-zA-Z0-9-]+', text)

# получение списка песен

import urllib.request

user_agent = 'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.0.7) Gecko/2009021910 Firefox/3.0.7'

print(albums)

#exit()

with open('Source/Oxxxymiron.txt', 'a+', encoding='utf-8') as ouf:
    for album_url in albums:
        headers={'User-Agent':user_agent,} 

        request=urllib.request.Request(album_url,None,headers) #The assembled request
        response = urllib.request.urlopen(request)
        data = response.read().decode('utf-8') # The data u need

        #print(data)

        songs = [re.search(r'https://genius.com/.*?"', i).group()[:-1] for i in re.findall(
            r'href="https://genius.com/.*" class="u-display_block">.*\n.*\n.*\n.*\n.*\n.*\n.*\n.*\n.*\n\s+\n', data)]

        print(*songs, sep='\n')

        #print(len(songs), url)

        album = ''

        for song_url in songs:
            request=urllib.request.Request(song_url,None,headers) #The assembled request
            response = urllib.request.urlopen(request)
            data = response.read().decode('utf-8') # The data u need

            text = re.sub(r'\n\s*\r', '', re.sub(r'\[.+\]\n', '', re.sub(r'</p>.+', '', re.sub(r'.+<p>', '', re.sub(r'<i>|</i>|</a>|<br>', '', re.sub(r'<a.*?>', '', re.findall(r'<div class="lyrics">\n.*\n.*<!--sse-->.+<!--/sse-->', data, re.S)[0], flags=re.S)), flags=re.S), flags=re.S)))

            album += text + '\n#\n'
            #print(text)
    
        ouf.write(album)