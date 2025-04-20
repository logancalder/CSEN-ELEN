; vi:ai:lisp:sm

(define (quicksort compare lst)
  (if (null? lst)
      lst
      (let* ((x (car lst))
             (xs (cdr lst))
             (below (lambda (y) (< (compare y x) 0)))
             (above (lambda (y) (>= (compare y x) 0))))
        (append (quicksort compare (filter below xs))
                (cons x (quicksort compare (filter above xs)))))))

; Compare two values X and Y for > < or =
(define (compare x y)
    (cond 
        ((< x y) - 1) 
        ((> x y) 1) 
        ((equal? x y) 0)))