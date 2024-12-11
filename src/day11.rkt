#lang racket
(require memo)

;return number of stones after blinks, for one stone with starting value n
(define/memoize (blink n blinks)
  (let* ((digits (count-digits n 0))
         (pow10 (expt 10 (/ digits 2))))
    (cond ((= blinks 0) 1)
          ((= n 0) (blink 1 (- blinks 1)))
          ((= (modulo digits 2) 0)
           (+ (blink (quotient n pow10) (- blinks 1))
              (blink (modulo n pow10) (- blinks 1))))
          (else (blink (* n 2024) (- blinks 1))))))

;Return number of digits in n
;When calling, give a starting value of 0 for acc
(define (count-digits n acc)
  (if (= n 0) acc
      (count-digits (quotient n 10) (+ acc 1))))

;Returns total number of stones after blinks for a list of stones
;eg. (solve '(125 17) 25) returns 55312
(define (solve lst blinks)
  (foldl (λ (x a) (+ (blink x blinks) a)) 0 lst))