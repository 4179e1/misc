(define (max a b) (if (> a b) a b))

(define (trimax x y z) 
 	(if ( = x (max x y)) 
		(max x (max y z))
		(max y (max x z))
	)
)

(define (max2sum x y z)
 	(
	if (= x (max x y))
		(+ x (max y z))
		(+ y (max x z))
	)
)

(trimax 3 2 1)
