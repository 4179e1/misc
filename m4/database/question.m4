define(`QUESTION_1',
`Why did the chicken cross the road?
ANSWER(`To get to the other side')
')

define(ANSWER, ifdef(`ANSWER_KEY', `Answer: $1<br />', `<br />'))
