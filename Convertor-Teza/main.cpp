#include <SFML/Graphics.hpp>
#include<vector>
#include<fstream>
#include<iostream>
using namespace std;
using namespace sf;
ifstream fin("Config.in");
RenderWindow Fereastra;
Font FontButoane;
Texture ImgFundal;
Sprite ImagineFundal;
Vector2i PozitieMouse;
class Buton;
vector<Buton> Butoane;
void Click()
{
    cout<<"MERGEEE"<<'\n';
}
class Buton
{
private:
    int x,y,lungime,latime,text_dimensiune, textOfsetX,textOfsetY;
    Text text;
    Color culoare;
    RectangleShape FormaButon;
    void CreazaForma()
    {
        FormaButon.setPosition(x,y);
        FormaButon.setSize(Vector2f(lungime,latime));
        FormaButon.setFillColor(culoare);
    }
    void CreazaTextul()
    {
        text.setCharacterSize(text_dimensiune);
        text.setFillColor(Color::White);
        text.setFont(FontButoane);
        text.setPosition(Vector2f(x+textOfsetX,y+textOfsetY));
    }
public:
    void (*Functie)(void);
    bool MousePesteButon, Selectat;
    Buton(int pos_x, int pos_y, int lg, int lat, Color cul,string txt, int dimensiune_text, int text_ofsetX, int text_ofsetY)
    {
        x=pos_x;
        y=pos_y;
        lungime=lg;
        latime=lat;
        text_dimensiune=dimensiune_text;
        textOfsetX=text_ofsetX;
        textOfsetY=text_ofsetY;
        text.setString(txt);
        culoare=cul;
        CreazaForma();
        CreazaTextul();
    }
    void DeseneazaButon()
    {
        Fereastra.draw(FormaButon);
        Fereastra.draw(text);
    }
    void MousePeste()
    {
        MousePesteButon=true;
        Color culoareMousePeste=Color(culoare.r-20,culoare.g-20,culoare.b-20);
        Color culoareText=text.getFillColor();
        Color culoareTextMousePeste=Color(culoareText.r-20,culoareText.g-20,culoareText.g-20);
        FormaButon.setFillColor(culoareMousePeste);
        text.setFillColor(culoareTextMousePeste);
    }
    void MouseNormal()
    {
        text.setFillColor(Color::White);
        MousePesteButon=false;
        FormaButon.setFillColor(culoare);
    }
    Vector2i PozitieButon()
    {
        Vector2i pos;
        pos.x=x;
        pos.y=y;
        return pos;
    }
    int lungimeButon()
    {
        return lungime;
    }
    int latimeButon()
    {
        return latime;
    }
    void CandFacemClick()
    {
        Functie();
    }
};
Buton CreezaButon(int pos_x, int pos_y, int lg, int lat, Color cul,string txt, int dimensiune_text, int text_ofsetX, int text_ofsetY,void(*functie)(void))
{
    Buton Bt(pos_x, pos_y,lg,lat,cul,txt,dimensiune_text,text_ofsetX,text_ofsetY);
    Bt.Functie=functie;
    Butoane.push_back(Bt);
    return Bt;
}
void DeseneazaButoane()
{
    for(int i=0;i<Butoane.size();i++)
    {
        Butoane[i].DeseneazaButon();
    }
}
void VerificaDacaButoaneleSuntSelectate()
{
    for(int i=0; i<Butoane.size();i++)
    {
        Vector2i ButonPos=Butoane[i].PozitieButon();
        if(PozitieMouse.x>=ButonPos.x&&PozitieMouse.x<=Butoane[i].lungimeButon()&&PozitieMouse.y>=ButonPos.y&&PozitieMouse.y<=Butoane[i].latimeButon())
        {
            Butoane[i].MousePeste();
            if(Mouse::isButtonPressed(Mouse::Left))
            {
                Butoane[i].CandFacemClick();
            }
        }
        else
        {
            Butoane[i].MouseNormal();
        }
    }
}

int main()
{
    FontButoane.loadFromFile("gibi_tm.ttf");
    ImgFundal.loadFromFile("imagine_fundal.png");
    ImagineFundal.setTexture(ImgFundal);
    ImagineFundal.setScale(Vector2f(0.75,0.8));
    Buton B=CreezaButon(1 ,1, 100,70,Color::Blue,"Buton",20,30,20,Click);
    Fereastra.create(VideoMode(800,800),"Converter");
    while (Fereastra.isOpen())
    {
        Event event;
        PozitieMouse=Mouse::getPosition(Fereastra);
        while (Fereastra.pollEvent(event))
        {
            if (event.type == Event::Closed)
                Fereastra.close();
        }
        VerificaDacaButoaneleSuntSelectate();
        Fereastra.clear();
        Fereastra.draw(ImagineFundal);
        DeseneazaButoane();
        Fereastra.display();
    }
    return 0;
}
