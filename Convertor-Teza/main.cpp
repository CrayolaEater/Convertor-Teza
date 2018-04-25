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
int SpatiulDeTextCurentSelectat=-1, MaxCharactereTextIntrodus=10;
string TText;
class Buton;
class SpatiuDestinatTextului;
vector<Text> TexteStatice;
vector<Buton> Butoane;
vector<SpatiuDestinatTextului> SpatiiDeScrisText;
void Click()
{
    cout<<"MERGEEE"<<'\n';
}
class SpatiuDestinatTextului
{
public:
    Text TextulScris;
    int x,y, lungime,latime;
    RectangleShape Forma;
    Color culoare;
    int pos_text_x, pos_text_y, dimensiuneText;

    void CreeazaForma()
    {
        Forma.setSize(Vector2f(lungime,latime));
        Forma.setPosition(Vector2f(x,y));
        Forma.setFillColor(culoare);
    }
    void CreeazaTextul()
    {
        TextulScris.setCharacterSize(dimensiuneText);
        TextulScris.setFillColor(Color::Black);
        TextulScris.setFont(FontButoane);
        TextulScris.setPosition(Vector2f(pos_text_x+x,pos_text_y+y));
    }
public:
    void DeseneazaSpatiuText()
    {
        Fereastra.draw(Forma);
        Fereastra.draw(TextulScris);
    }
    string TextScris;
    SpatiuDestinatTextului(int pos_x,int pos_y,int lg,int lat,Color Culoare,int pos_t_x,int pos_t_y,int dim_text)
    {
        x=pos_x;
        lungime=lg;
        latime=lat;
        y=pos_y;
        culoare=Culoare;
        pos_text_x=pos_t_x;
        pos_text_y=pos_t_y;
        dimensiuneText=dim_text;
        CreeazaTextul();
        CreeazaForma();
    }
    void ActualizeazaTextul()
    {
        TextulScris.setString(TextScris);
    }
    bool MouseEstePeste()
    {
        if (Forma.getGlobalBounds().contains(Fereastra.mapPixelToCoords(PozitieMouse)))
        {
            return true;
        }
        return false;
    }
};
class Buton
{
private:
    Text text;
    Color culoare, Evidentiat;
    RectangleShape FormaButon;
    Uint8 CantitateCuloareRedusa=20;
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
    int x,y,lungime,latime,text_dimensiune, textOfsetX,textOfsetY;
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
        Evidentiat.a=culoare.a/8;
        FormaButon.setFillColor(Evidentiat);
    }
    void MouseNormal()
    {
        text.setFillColor(Color::White);
        MousePesteButon=false;
        FormaButon.setFillColor(culoare);
    }
    void CandFacemClick()
    {
        Functie();
    }
    bool MouseEstePeste()
    {
        if (FormaButon.getGlobalBounds().contains(Fereastra.mapPixelToCoords(PozitieMouse)))
        {
            MousePeste();
            return true;
        }
        MouseNormal();
        return false;
    }
};
Buton CreezaButon(int pos_x, int pos_y, int lg, int lat, Color cul,string txt, int dimensiune_text, int text_ofsetX, int text_ofsetY,void(*functie)(void))
{
    Buton Bt(pos_x, pos_y,lg,lat,cul,txt,dimensiune_text,text_ofsetX,text_ofsetY);
    Bt.Functie=functie;
    Butoane.push_back(Bt);
    return Bt;
}
SpatiuDestinatTextului CreeazaSpatiuPentruScris(int pos_x,int pos_y,int lg,int lat,Color Culoare,int pos_t_x,int pos_t_y,int dim_text)
{
    SpatiuDestinatTextului SpTxT(pos_x,pos_y,lg,lat,Culoare,pos_t_x,pos_t_y,dim_text);
    SpatiiDeScrisText.push_back(SpTxT);
    return SpTxT;
}
void DeseneazaButoane()
{
    for(int i=0; i<Butoane.size(); i++)
    {
        Butoane[i].DeseneazaButon();
    }
}
void DeseneazaSpatiiScris()
{
    for(int i=0; i<SpatiiDeScrisText.size(); i++)
    {
        SpatiiDeScrisText[i].DeseneazaSpatiuText();
    }
}
void VerificaDacaButoaneleSuntSelectate()
{
    for(int i=0; i<Butoane.size(); i++)
    {
        if(Butoane[i].MouseEstePeste())
        {
            if(Mouse::isButtonPressed(Mouse::Left))
            {
                Butoane[i].CandFacemClick();
            }
        }
    }
}
void VerificaDacaTextulEsteSelectat()
{
    for(int i=0; i<SpatiiDeScrisText.size(); i++)
    {
        if(SpatiiDeScrisText[i].MouseEstePeste())
        {
            if(Mouse::isButtonPressed(Mouse::Left))
            {
                SpatiulDeTextCurentSelectat=i;
                if(SpatiiDeScrisText[i].TextScris.size()==0)
                {
                    TText.erase(TText.begin(),TText.end());
                }
                else
                {
                    TText=SpatiiDeScrisText[i].TextScris;
                }
            }
        }
    }
}
void VerificaTextIntrodusTastatura(Event event)
{
    if (event.type == Event::TextEntered)
    {
        if ((event.text.unicode <= 57&& event.text.unicode>=48 && SpatiulDeTextCurentSelectat>-1)||(SpatiulDeTextCurentSelectat>-1&&event.text.unicode==46))
        {
            if(TText.size()<=MaxCharactereTextIntrodus)
            {
                TText+=static_cast<char>(event.text.unicode);
                SpatiiDeScrisText[SpatiulDeTextCurentSelectat].TextScris=TText;
                SpatiiDeScrisText[SpatiulDeTextCurentSelectat].ActualizeazaTextul();
            }
            cout<<TText<<'\n';
            //cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
        }
    }
}
void CreeazaStaticText(int pos_x,int pos_y, int dimensiune,string txt,Color culoare)
{
    Text text;
    text.setFont(FontButoane);
    text.setPosition(Vector2f(pos_x,pos_y));
    text.setCharacterSize(dimensiune);
    text.setFillColor(culoare);
    text.setString(txt);
    TexteStatice.push_back(text);
}
void DeseneazaTexteleStatice()
{
    for(int i =0; i<TexteStatice.size();i++)
    {
        Fereastra.draw(TexteStatice[i]);
    }
}
int main()
{
    FontButoane.loadFromFile("BALLSONTHERAMPAGE.ttf");
    ImgFundal.loadFromFile("imagine_fundal.png");
    ImagineFundal.setTexture(ImgFundal);
    ImagineFundal.setScale(Vector2f(0.9,.8));
    //Buton B=CreezaButon(2,30, 100,70,Color::Blue,"Buton",20,30,20,Click);
    SpatiuDestinatTextului TextPtValoriDeIntrodus=CreeazaSpatiuPentruScris(10, 150,400,30,Color::Blue,5,-8,35);
    CreeazaStaticText(10,117,35,"Valoare:",Color::White);
    CreeazaStaticText(230,1,80,"Converter",Color::White);
    Fereastra.create(VideoMode(800,800),"Converter");
    while (Fereastra.isOpen())
    {
        Event event;
        PozitieMouse=Mouse::getPosition(Fereastra);
        while (Fereastra.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                Fereastra.close();
            }
            VerificaTextIntrodusTastatura(event);
        }
        Fereastra.clear();
        VerificaDacaButoaneleSuntSelectate();
        VerificaDacaTextulEsteSelectat();
        Fereastra.draw(ImagineFundal);
        DeseneazaButoane();
        DeseneazaSpatiiScris();
        DeseneazaTexteleStatice();
        Fereastra.display();
    }
    return 0;
}
