#!/usr/bin/python
#coding:utf-8
from bs4 import BeautifulSoup

doc=u"""<div class="g"><!--m--><div class="rc" data-hveid="77"><h3 class="r"><a href="http://www.azlyrics.com/lyrics/adele/hello.html" onmousedown="return rwt(this,'','','','8','AFQjCNGKw-Rpxymd0eXOsFOS9llvsg3gVw','','0ahUKEwjBwbeW5-DLAhUUzWMKHU7-D1YQFghOMAc','','',event)">ADELE LYRICS - Hello - A-Z Lyrics</a></h3><div class="s"><div><div class="f kv _SWb" style="white-space:nowrap"><cite class="_Rm">www.azlyrics.com/lyrics/adele/<b>hello</b>.html</cite> - <a class="fl" href="https://translate.google.co.jp/translate?hl=zh-CN&amp;sl=en&amp;u=http://www.azlyrics.com/lyrics/adele/hello.html&amp;prev=search" onmousedown="return rwt(this,'','','','8','AFQjCNHnFEYuoomMgGd4457oi6YVtxziRw','','0ahUKEwjBwbeW5-DLAhUUzWMKHU7-D1YQ7gEIUDAH','','',event)">翻译此页</a></div><span class="st"><em>Hello</em>, it's me. I was wondering if after all these years you'd like to meet. To go over everything. They say that time's supposed to heal ya. But I ain't done much&nbsp;...</span></div></div></div><!--n--></div>"""

soup = BeautifulSoup (doc, "lxml")
h3 = soup.find ('h3')
title = h3.a.string
href = h3.a['href']
#title = soup.div.div.h3.a.string
#href = soup.div.div.h3.a['href']

# cite and dess were pre-formatted
cite = soup.find(class_='_Rm')
desc = soup.find('span')

print (title)
print (href)
print (cite)
print (desc)

