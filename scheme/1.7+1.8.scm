(define (cube-root x)
	(define (cube-root-iter guess x)
	 	(if (good-enough? guess x)
			guess
			(cube-root-iter (improve guess x) x)
		)
	)
	
	;square were a builtin function
	(define (improve guess x)
	 	(/ (+ (/ x (square guess)) (* 2 guess)) 3)
	)
	
	(define (good-enough? guess x)
	 	(= guess (improve guess x))
	)

 	(cube-root-iter 1.0 x)
)

(cube-root 8)
(cube-root -8)
(cube-root 0.001)
(cube-root 1000000000)
