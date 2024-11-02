t := Tree new .
value := stdin nextLine asNumber .

[ value = -1 ] whileFalse: [
    t insert: value .
    value := stdin nextLine asNumber .
] .

value := stdin nextLine asNumber .

[ value = -1 ] whileFalse: [
    (t member: value) printNl .
    value := stdin nextLine asNumber .
] .

(t maximum) printNl.