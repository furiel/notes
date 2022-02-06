(ns user
  (:require [integrant.repl :as ir]
            [integrant.core :as ig]))

(defn set-prep! []
  (ir/set-prep! (constantly (ig/read-string (slurp "config.edn")))))

(set-prep!)

(defn reset []
  (set-prep!)
  (ir/reset))

(comment
  (reset))
