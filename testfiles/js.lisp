(module js)
(import 
  ("other" setter) 
  ("types" custom))

(type Narrow (
  str custom
  val string
  status number))

(inline fs)