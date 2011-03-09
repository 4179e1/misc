cat >$$ <<EOF
X-Original-To: lyre
Delivered-To: lyre@linux.site
Date: Fri, 04 Mar 2011 22:27:52 +0800
To: lyre@linux.site
Subject: hello
User-Agent: Heirloom mailx 12.2 01/07/07
MIME-Version: 1.0
Content-Type: text/plain; charset=us-ascii
Content-Transfer-Encoding: 7bit
From: lyre@linux.site (lyre)

hello world!
EOF

ed &>/dev/null $$ <<EOF
1, /^[ ]*$/d
w
q
EOF

cat $$

rm -rf $$
