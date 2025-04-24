#!/bin/bash


base_url="https://readi.fi/sitemap.xml";
pattern="https://readi.fi/asset"
sql_injection_pattern="((('|\")\s*(OR|AND)\s*('|\"|\d))|(--|;)|(\b(SELECT|UNION|INSERT|UPDATE|DELETE|DROP)\b.*\b(FROM|INTO|TABLE)\b)|(\b(OR|AND)\b\s+\d=\d))"
site=$(curl -s "$base_url" | grep -o '<loc[^>]*>[^<]*</loc>' | sed -e 's/<loc>//g' -e 's/<\/loc>//g' | grep -e $pattern)

for link in $site;do
	title=$(curl -s "${link}" | grep -o '<title[^>]*>[^<]*</title>' | sed -e 's/<title>//g' -e 's/<\/title>//g')
	meta=$(curl -s "${link}" | grep -o '<meta name="description" content="[^"]*"' | sed 's/.*content="\([^"]*\)".*/\1/')
	if (echo "$title"|grep -E "$sql_injection_pattern") || (echo "$meta"|grep -Ei "$sql_injection_pattern"); then 
	       echo "SQL injection detected"
       else
	       sh ./db.sh "$title $meta"
       	       echo "Text succesfuully appened"
	fi
done


# Que se passe t'il si le titre de la page est "L'avenir de Westen UNION" ?
# Cela va trigger le echo "SQL injection detected" alors que ce n'est pas une injection sql
# Potentiellement on se retrouve avec des faux positifs dans les logs etc.

# C'est le fait de concaténer les arguments à la requête sql qui permet des injections sql
# Typiquement si $1=toto, $2=toto et $3 = "toto'); DROP TABLE data;" 
# La requête sql devient
# INSERT INTO data (url, title, description) values ('toto', 'toto', 'toto'); DROP TABLE data;

# Pour éviter cela il faut utiliser des requêtes préparées
# "INSERT INTO data (url, title, description) values (?, ?, ?);" "$1" "$2" "$3"

# Ansi, si $3 = "toto'); DROP TABLE data;"
# La requête sql devient
# INSERT INTO data (url, title, description) values ("toto", "toto", "toto'); DROP TABLE data;");