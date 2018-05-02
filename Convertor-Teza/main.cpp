#include <SFML/Graphics.hpp>
#include<vector>
#include<fstream>
#include<iostream>
#include<string>
using namespace std;
using namespace sf;
fstream ConfigInput;
float ValoareNouaConvertor;
RenderWindow Fereastra, SchimbaValoarea;
Font FontButoane;
Text ValoarePrecedenta;
Texture ImgFundal;
Sprite ImagineFundal;
Vector2i PozitieMouse;
bool DeschisFereastraSchimbaValoarea;
int SpatiulDeTextCurentSelectat=-1, MaxCharactereTextIntrodus=10,FereastraCurentaID=1, PozitieValoareDeModificat,IndiceButonSelectat=-1;
string TText;
class Buton;
class SpatiuDestinatTextului;
struct TexteStaticee
{
    Text text;
    int FereastraID;
};
vector<TexteStaticee> TexteStatice;
vector<Buton> Butoane;
vector<SpatiuDestinatTextului> SpatiiDeScrisText;
vector<float>ValoriConvertor;
class SpatiuDestinatTextului
{
public:
    Text TextulScris;
    Texture textura;
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
    int FereastraID;
    void DeseneazaSpatiuText()
    {
        Fereastra.draw(Forma);
        Fereastra.draw(TextulScris);
    }
    void DeseneazaSpatiuText2()
    {
        SchimbaValoarea.draw(Forma);
        SchimbaValoarea.draw(TextulScris);
    }
    string TextScris;
    SpatiuDestinatTextului(int pos_x,int pos_y,int lg,int lat,Color Culoare,int pos_t_x,int pos_t_y,int dim_text,string textuRa)
    {
        textura.loadFromFile(textuRa);
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
        Forma.setTexture(&textura);
    }
    void ActualizeazaTextul()
    {
        TextulScris.setString(TextScris);
    }
    bool MouseEstePeste()
    {
        if(FereastraCurentaID==1)
        {
            if (Forma.getGlobalBounds().contains(Fereastra.mapPixelToCoords(PozitieMouse)))
            {
                Color Grey(183,183,183);
                Forma.setFillColor(Grey);
                return true;
            }
            Forma.setFillColor(Color::White);
            return false;
        }
        else
        {
            if (Forma.getGlobalBounds().contains(SchimbaValoarea.mapPixelToCoords(PozitieMouse)))
            {
                Color Grey(183,183,183);
                Forma.setFillColor(Grey);
                return true;
            }
            Forma.setFillColor(Color::White);
        }
    }
};
class Buton
{
private:
    Texture textura;
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
    void caca()
    {
        printf("cacca");
    }
    Text text;
    int x,y,lungime,latime,text_dimensiune, textOfsetX,textOfsetY,IndiceValoare,FereastraID;
    void (*Functie)(void);
    bool MousePesteButon, Selectat,Apasat;
    Buton(int pos_x, int pos_y, int lg, int lat, string txt, int dimensiune_text, int text_ofsetX, int text_ofsetY,string stringImagine,int indice_valoare)
    {
        textura.loadFromFile(stringImagine);
        x=pos_x;
        y=pos_y;
        lungime=lg;
        latime=lat;
        text_dimensiune=dimensiune_text;
        textOfsetX=text_ofsetX;
        textOfsetY=text_ofsetY;
        text.setString(txt);
        culoare=Color::White;
        CreazaForma();
        CreazaTextul();
        IndiceValoare=indice_valoare;
        FormaButon.setTexture(&textura);
    }
    void DeseneazaButon()
    {
        Fereastra.draw(FormaButon);
        Fereastra.draw(text);
    }
    void DeseneazaButon2()
    {
        SchimbaValoarea.draw(FormaButon);
        SchimbaValoarea.draw(text);
    }
    void MousePeste()
    {
        Color Grey(183,183,183);
        MousePesteButon=true;
        FormaButon.setFillColor(Grey);
    }
    void MouseNormal()
    {
        MousePesteButon=false;
        FormaButon.setFillColor(culoare);
    }
    void CandFacemClick()
    {
        Functie();
    }
    bool MouseEstePeste()
    {
        if(FereastraCurentaID==1)
        {
            if (FormaButon.getGlobalBounds().contains(Fereastra.mapPixelToCoords(PozitieMouse)))
            {
                MousePeste();
                return true;
            }
            MouseNormal();
            return false;
        }
        else
        {
            if (FormaButon.getGlobalBounds().contains(SchimbaValoarea.mapPixelToCoords(PozitieMouse)))
            {
                MousePeste();
                return true;
            }
            MouseNormal();
            return false;
        }
    }
};
Buton CreezaButon(int pos_x, int pos_y, int lg, int lat, string txt, int dimensiune_text, int text_ofsetX, int text_ofsetY,void(*functie)(void),string imagine,int indiceValoare,int IDfereastra)
{
    Buton Bt(pos_x, pos_y,lg,lat,txt,dimensiune_text,text_ofsetX,text_ofsetY,imagine,indiceValoare);
    Bt.Functie=functie;
    Bt.FereastraID=IDfereastra;
    Butoane.push_back(Bt);
    return Bt;
}
SpatiuDestinatTextului CreeazaSpatiuPentruScris(int pos_x,int pos_y,int lg,int lat,Color Culoare,int pos_t_x,int pos_t_y,int dim_text,string imagine,int IDfereastra)
{
    SpatiuDestinatTextului SpTxT(pos_x,pos_y,lg,lat,Culoare,pos_t_x,pos_t_y,dim_text,imagine);
    SpTxT.FereastraID=IDfereastra;
    SpatiiDeScrisText.push_back(SpTxT);
    return SpTxT;
}
void DeseneazaButoane()
{
    for(int i=0; i<Butoane.size(); i++)
    {
        bool principal=(Butoane[i].FereastraID==1);
        if(principal)
        {
            Butoane[i].DeseneazaButon();
        }
        else
        {
            Butoane[i].DeseneazaButon2();
        }
    }
}
void DeseneazaSpatiiScris()
{
    for(int i=0; i<SpatiiDeScrisText.size(); i++)
    {
        bool principal=(SpatiiDeScrisText[i].FereastraID==1);
        if(principal)
        {
            SpatiiDeScrisText[i].DeseneazaSpatiuText();
        }
        else
        {
            SpatiiDeScrisText[i].DeseneazaSpatiuText2();
        }
    }
}
void VerificaDacaButoaneleSuntSelectate()
{
    for(int i=0; i<Butoane.size(); i++)
    {
        if(Butoane[i].MouseEstePeste())
        {
            if(Mouse::isButtonPressed(Mouse::Left)&&!Butoane[i].Apasat)
            {
                IndiceButonSelectat=i;
                Butoane[i].CandFacemClick();
                Butoane[i].Apasat=true;
            }
            else if(!Mouse::isButtonPressed(Mouse::Left))
            {
                IndiceButonSelectat=-1;
                Butoane[i].Apasat=false;
            }
        }
        else
        {
            IndiceButonSelectat=-1;
            Butoane[i].Apasat=false;
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
        if ((event.text.unicode <= 57&& event.text.unicode>=48 && SpatiulDeTextCurentSelectat>-1)||(SpatiulDeTextCurentSelectat>-1&&event.text.unicode==46)||(SpatiulDeTextCurentSelectat>-1&&event.text.unicode==8))
        {
            if(event.text.unicode==8&&TText.size()>0)
            {
                TText.erase(TText.size()-1,1);
                SpatiiDeScrisText[SpatiulDeTextCurentSelectat].TextScris=TText;
                SpatiiDeScrisText[SpatiulDeTextCurentSelectat].ActualizeazaTextul();
                return;
            }
            if(TText.size()<=MaxCharactereTextIntrodus)
            {
                if(event.text.unicode!=8)
                {
                    TText+=static_cast<char>(event.text.unicode);
                }
                SpatiiDeScrisText[SpatiulDeTextCurentSelectat].TextScris=TText;
                SpatiiDeScrisText[SpatiulDeTextCurentSelectat].ActualizeazaTextul();
            }
            //cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
        }
    }
}
void CreeazaStaticText(int pos_x,int pos_y, int dimensiune,string txt,Color culoare,int IDfereastra)
{
    Text text;
    text.setFont(FontButoane);
    text.setPosition(Vector2f(pos_x,pos_y));
    text.setCharacterSize(dimensiune);
    text.setFillColor(culoare);
    text.setString(txt);
    TexteStaticee txtt;
    txtt.text=text;
    txtt.FereastraID=IDfereastra;
    TexteStatice.push_back(txtt);
}
void DeseneazaTexteleStatice()
{
    for(int i =0; i<TexteStatice.size(); i++)
    {
        bool principal=(TexteStatice[i].FereastraID==1);
        if(principal)
        {
            Fereastra.draw(TexteStatice[i].text);
        }
        else
        {
            SchimbaValoarea.draw(TexteStatice[i].text);
        }
    }
}
void ModificaValoareInConvertor(int indice, float valoare)
{
    ValoriConvertor[indice]=valoare;
}
void CitesteValoriConvertor()
{
    ConfigInput.open("Config.in",ios::in);
    float valoare;
    while(ConfigInput>>valoare)
    {
        ValoriConvertor.push_back(valoare);
    }
    ConfigInput.close();
    ConfigInput.clear();
}
void AfiseazaValoriConvertor()
{
    ConfigInput.open("Config.in",ios::out);
    for(int i =0; i<ValoriConvertor.size(); i++)
    {
        ConfigInput<<ValoriConvertor[i]<<'\n';
    }
    ConfigInput.close();
}
void VerificaTastaEnterCandTextulEsteIntrodus()
{

}
string FloatToString(float nr);
void ActualizeazaValorileButoanelor()
{
    for(int i =0; i<Butoane.size(); i++)
    {
        if(Butoane[i].FereastraID==1&&Butoane[i].IndiceValoare>=0)
        {
            Butoane[i].text.setString(FloatToString(ValoriConvertor[Butoane[i].IndiceValoare]));
            //cout<<"Butonul "<<i<<" are indicele:"<<Butoane[i].IndiceValoare<<'\n';
        }
    }
}
void StergeElementeleDinFereastraSecundara()
{
    for(int i=0; i<TexteStatice.size(); i++)
    {
        if(TexteStatice[i].FereastraID==2)
        {
            TexteStatice.erase(TexteStatice.begin()+i,TexteStatice.begin()+i+1);
        }
    }
    for(int i=0 ; i<SpatiiDeScrisText.size();i++)
    {
        if(SpatiiDeScrisText[i].FereastraID==2)
        {
            SpatiiDeScrisText.erase(SpatiiDeScrisText.begin()+i,SpatiiDeScrisText.begin()+i+1);
        }
    }
}
void DeschideFereastraDeSchimbatValoarea()
{
    CreeazaStaticText(3,5,30,"Valoare Precedenta:",Color::White,2);
    CreeazaStaticText(40,30,30,FloatToString(ValoriConvertor[Butoane[IndiceButonSelectat].IndiceValoare]),Color::Green,2);
    CreeazaStaticText(3,55,30,"Valoare Noua:",Color::White,2);
    SpatiuDestinatTextului ValoareNoua=CreeazaSpatiuPentruScris(3,85,250,30,Color::Blue,0,0,30,"butoane/LocScris_imagine.png",2);
    SchimbaValoarea.create(VideoMode(300,300),"Schimba Valoarea");
    DeschisFereastraSchimbaValoarea=true;
    FereastraCurentaID=2;
}
void ClickSaModificeValoareConvertor()
{
    PozitieValoareDeModificat=Butoane[IndiceButonSelectat].IndiceValoare;
    cout<<"butonul "<<IndiceButonSelectat<<" trebuie sa modifice valoarea de pe "<<Butoane[IndiceButonSelectat].IndiceValoare<<'\n';
    if(!DeschisFereastraSchimbaValoarea)
    {
        DeschideFereastraDeSchimbatValoarea();
        cout<<"MERGEEE"<<'\n';
    }
}
string FloatToString(float nr)
{
    vector<int> v;
    v.empty();
    string cc;
    cc.empty();
    int nr2=nr;
    int cnr2=nr2;
    while(cnr2)
    {
        v.push_back(cnr2%10);
        cnr2/=10;
    }
    for(int i=v.size()-1; i>=0; i--)
    {
        cc+=v[i]+48;
    }
    cc+='.';
    while(nr)
    {
        nr-=nr2;
        nr*=10;
        nr2=nr;
        cc+=nr2+48;
    }
    cc.erase(cc.begin()+v.size()+4,cc.end());
    return cc;
}
void Click2()
{
    cout<<"MERGEEE"<<'\n';
}
int main()
{
    FontButoane.loadFromFile("BALLSONTHERAMPAGE.ttf");
    ImgFundal.loadFromFile("imagine_fundal.png");
    ImagineFundal.setTexture(ImgFundal);
    CitesteValoriConvertor();
    ModificaValoareInConvertor(2,3.3333);
    ImagineFundal.setScale(Vector2f(0.9,.8));
    Buton B_Euro=CreezaButon(10,200, 200,70,"0.000",30,10,0,ClickSaModificeValoareConvertor,"butoane/buton_euro.png",0,1);
    //Buton B_Euro2=CreezaButon(1,1, 200,70,"0.000",30,10,0,Click2,"butoane/buton_euro.png",0,2);
    Buton B_Dolar=CreezaButon(220,200, 200,70,"0.000",30,10,0,ClickSaModificeValoareConvertor,"butoane/buton_dolar.png",1,1);
    Buton B_LiraSterlina=CreezaButon(430,200, 200,70,"0.000",30,10,0,ClickSaModificeValoareConvertor,"butoane/buton_lira.png",2,1);
    Buton B_FrancElvetian=CreezaButon(640,200, 200,70,"0.000",30,10,0,ClickSaModificeValoareConvertor,"butoane/buton_franc.png",3,1);
    SpatiuDestinatTextului TextPtValoriDeIntrodus=CreeazaSpatiuPentruScris(10, 150,400,40,Color::Blue,20,0,33,"butoane/LocScris_imagine.png",1);
    CreeazaStaticText(30,117,35,"Valoare:",Color::White,1);
    CreeazaStaticText(250,1,80,"Converter",Color::White,1);
    Fereastra.create(VideoMode(840,800),"Converter");
    ActualizeazaValorileButoanelor();
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
        while(SchimbaValoarea.isOpen())
        {
            PozitieMouse=Mouse::getPosition(SchimbaValoarea);
            Event event2;
            while (SchimbaValoarea.pollEvent(event2))
            {
                if (event2.type == Event::Closed)
                {
                    SchimbaValoarea.close();
                    DeschisFereastraSchimbaValoarea=false;
                    FereastraCurentaID=1;
                    IndiceButonSelectat=-1;
                    StergeElementeleDinFereastraSecundara();
                }
                VerificaTextIntrodusTastatura(event2);
            }
            SchimbaValoarea.clear();
            VerificaDacaButoaneleSuntSelectate();
            VerificaDacaTextulEsteSelectat();
            SchimbaValoarea.draw(ImagineFundal);
            DeseneazaButoane();
            DeseneazaSpatiiScris();
            DeseneazaTexteleStatice();
            SchimbaValoarea.display();
        }
    }
    AfiseazaValoriConvertor();
    return 0;
}
