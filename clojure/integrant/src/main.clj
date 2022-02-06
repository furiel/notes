(ns main
  (:require [integrant.core :as ig]))

(defn main [name]
  (println "Starting process")
  (println "Hello " name)
  (println "Finished"))

(defmethod ig/init-key :main [_ {:keys [name]}]
  (future (main name)))
