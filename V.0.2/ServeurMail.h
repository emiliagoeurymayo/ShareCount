#ifndef SERVEURMAIL
#define SERVEURMAIL

#include <string>
#include <list>

class ServeurMail{
public:

    ServeurMail();//Constructeur
    virtual ~ServeurMail();
    void ajouterEmail(std::string email);
    bool getStatusEmail(std::string email);

private:

    std::list<std::string> listeMailValide;

};

#endif // SERVEURMAIL
