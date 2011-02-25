divert(-1) dnl
define(`START_HTML',
`<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
	<meta name="Author" content="Lyre">
	<title>$1</title>
</head>
<body test="#000000"
	ifdef (`BACKGROUD_IMAGE', `backgroud="BACKGROUD_IMAGE"')
	bgcolor="#eeeeee" link="#3333ff"
	vlink=#000099"
	alink="#ffffff">
')

define(`PAGE_HEADER',
`<table border="0" backgroud="steel.jpg"
width="100%">
	<tr>
		<td align="left">$1</td>
		<td align="right">$2</td>
	</tr>
</table>
<div align=right>
	Last Modified: esyscmd(`date')
</div>
')

define(`HTML_BANNER',
`<table border="0"
backgroud="steel.jpg"
width="100%">
	<tr>
		<td>
			<image src="$2">
			<h2>$1</h2>
		</td>
	</tr>
</table>
')

define(`END_HTML', `</body></html>')
divert dnl
