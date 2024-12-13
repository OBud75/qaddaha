
class Person():
    age = None

    def id_major(self):
        return self.age >= 18

toto = Person()
toto.age = 20
titi = Person()
titi.age = 15
nana = Person()
nana.age = 56
nono = Person()
nono.age = 42

a = toto.id_major()
b = not(titi.id_major())
c = nana.id_major()
d = nono.id_major()



f = not(a and (not b) and (a or b)) or (not a and b) and not (a or (not b) or (not c))
f_fix = not a or b or c

# not(a and (not b) and (a or b)) se simplifie en not a or b
# (not a and b) and not (a or (not b) or (not c)) se simplifie en b and c
# Combinaison des deux parties : (not a or b) or (b and c) se simplifie en not a or b or c

g = not((c or d)) and a and not(c) and d and ((not a) and c or (not d))
g_fix = a and not c and d

# not((c or d)) se simplifie en not c and not d
# Combinaison avec a and not(c) and d : a and not c and d
# ((not a) and c or (not d)) est redondant lorsqu'il est combiné avec la simplification précédente

s1 = a and (a or b)
s1_fix = a

# (a or b) est toujours vrai si a est vrai
# Par conséquent, a and (a or b) se simplifie en a

s2 = (a or b) and ((not a) or b)
s2_fix = b

# ((not a) or b) est toujours vrai si b est vrai
# Par conséquent, (a or b) and ((not a) or b) se simplifie en b

s3 = (a and (not b) or c) and (a or (not b))
s3_fix = a or c

# (a and (not b) or c) se simplifie en a or c
# (a or (not b)) est redondant lorsqu'il est combiné avec la simplification précédente

s4 = (a and b) or c and (not a) or (b and c) and (not b)
s4_fix = c

# (a and b) est redondant lorsqu'il est combiné avec c and (not a)
# (b and c) and (not b) est toujours faux

s5 = (a or b or c) and (not a or b or c) or (a and b) or c and d 
s5_fix = a or b or c

s6 = a or b or (not c) and b or (a or not c) or not ((not a) or b or ((not a) and c))
s6_fix = a or b

# (not c) and b est toujours faux
# (a or not c) est redondant lorsqu'il est combiné avec a or b
# not ((not a) or b or ((not a) and c)) est toujours vrai
# Par conséquent, a or b est la seule partie de la formule qui est toujours vraie



print(f"\n f: {f} \n f_fix: {f_fix}")
print(f"\n g: {g} \n g_fix: {g_fix}")
print(f"\n s1: {s1} \n s1_fix: {s1_fix}")
print(f"\n s2: {s2} \n s2_fix: {s2_fix}")
print(f"\n s3: {s3} \n s3_fix: {s3_fix}")
print(f"\n s4: {s4} \n s4_fix: {s4_fix}")
print(f"\n s5: {s5} \n s5_fix: {s5_fix}")








