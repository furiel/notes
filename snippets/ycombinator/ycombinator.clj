; based on https://blog.klipse.tech//lambda/2016/08/07/almost-y-combinator-clojure.html

(defn length [lst]
  (if (seq lst)
    (+ 1 (length (rest lst)))
    0))

(length '(1 'a :c))

(defn generate-length [f]
  (fn [lst]
    (if (seq lst)
      (+ 1 (f (rest lst)))
      0)))

((generate-length length) '(1 'a :c))

(defn callmyself-length [f]
  (fn [lst]
    (if (seq lst)
      (+ 1 ((f f) (rest lst)))
      0)))

((callmyself-length callmyself-length) '(1 'a :c))

(defn ycombinator [f]
  (f f))

(defn length-with-ycombinator [input]
  ((ycombinator
     (fn [f]
       (fn [lst]
         (if (seq lst)
           (+ 1 ((f f) (rest lst)))
           0))))
   input))

(length-with-ycombinator '(1 'a :c))
