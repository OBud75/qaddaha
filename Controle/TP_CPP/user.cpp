#include "user.hpp"
#include "pwd.hpp"
#include <iostream>
#include <unordered_map>
#include <memory>

static std::unordered_map<int, std::shared_ptr<User>> user_db;

User::User(int id, Password password) 
    : id(id), password(std::make_shared<Password>(std::move(password))), is_logged_in(false) {}

int User::login(const char *raw_password) {
    Password temp_password(raw_password);
    if (*password == temp_password) {
        is_logged_in = true;
        return 1;
    }
    return 0;
}

void User::save() {
    user_db[id] = std::make_shared<User>(id, *password);
    std::cout << "User ID " << id << " saved." << std::endl;
}

std::shared_ptr<User> User::get(int id) {
    if (user_db.find(id) != user_db.end()) {
        return user_db[id];
    } else {
        throw std::runtime_error("User not found !");
    }
}
// Dans l'idée je pensais à un vector<unique_ptr<User>>
// Dans tous les cas vous êtes un des seuls sur les 2 sections à avoir pensé à cette approche.
// Ce n'est pas forcément mieux que de renvoyer directement un smart pointer ni même une
// copie vu que l'application est très simple mais c'est bien ca que j'attendais.
// Je pensais plutôt à des pointeurs uniques pour que le conteneur soit dernier responsable
// de la mémoire (puis on utilise des copies ou références vers les objets du conteneur).
// Ici si un objet est supprimé du conteneur, c'est le code appelant qui se retrouve avec
// le dernier ownership (pas forcément moins bien, au contraire, tant que c'est voulu)

// Par contre le conteneur servirait uniquement de cache avec une méthode save qui enregistre
// dans un fichier/BDD. Ainsi on pourrait get des User déjà enregistrés dans le fichier
// avant le début du programme dans le fichier et les ajouter dans le conteneur.
// Si l'utilisateur est dans le cache, on garde votre solution, sinon on lit le fichier,
// on ajoute l'user au conteneur et on renvoie un smart pointer (ou pas en fonction des besoin)
// de l'objet qu'on vient d'ajouter au conteneur.
// L'ajout des User dans le conteneur pourrait même se faire dans le constructeur de User.
