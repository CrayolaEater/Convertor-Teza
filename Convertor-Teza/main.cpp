#include <SFML/Graphics.hpp>
#include<vector>
#include<fstream>
#include<iostream>
#include<string>
using namespace std;
using namespace sf;
fstream ConfigInput;
enum Marime {Bacnota,Dimensiune,Volum,FaraMasura,Grade,Greutate, Lungime, Presiune,Suprafata,Fahrenheit};
float ValoareNouaConvertor=1,ValoareIntrodusa;
RenderWindow Fereastra, SchimbaValoarea;
Font FontButoane;
Text ValoarePrecedenta,TipMasura;
Time timp;
Clock ceas;
Uint8 r,g,b;
Sprite Logoul, Meniu;
Texture ImgFundal;
Sprite ImagineFundal;
Vector2i PozitieMouse;
bool DeschisFereastraSchimbaValoarea,EsteButon,SchimbatCuloareFundal,EsteMeniul=true,ApasatTastaInMeniu,CautatButonuDeAdaugat;
int SpatiulDeTextCurentSelectat=-1, MaxCharactereTextIntrodus=6,FereastraCurentaID=1, PozitieValoareDeModificat,IndiceButonSelectat=-1,IndiceLogo,IndiceMeniu=1,IndiceButonDeAdaugare=24,IndiceButonNou,IndiceButonDeModificat;
string TText;
class Buton;
class SpatiuDestinatTextului;
struct TexteStaticee
{
    Text text;
    int FereastraID;
};
struct ButonCustom
{
    string Cale;
    bool activ;
};
vector<TexteStaticee> TexteStatice;
vector<Buton> Butoane;
vector<SpatiuDestinatTextului> SpatiiDeScrisText;
vector<float>ValoriConvertor;
vector<ButonCustom>ButoaneCustomCitite;
Texture Logo[10], MeniuSpriteuri[26];
class SpatiuDestinatTextului
{
private:
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
    Color culoare;
    Texture textura;
public:
    Text TextulScris;
    int x,y, lungime,latime;
    RectangleShape Forma;
    bool Apasat;
    void(*Functie)(void);
    int pos_text_x, pos_text_y, dimensiuneText, FereastraID;
    string TextScris;
    void CandApasamEnter()
    {
        Functie();
    }
    void GolesteSpatiuDeCharactere()
    {
        TextulScris.setString("");
    }
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
    void Normal()
    {
        Forma.setFillColor(Color::White);
        Apasat=false;
    }
    void MouseClick()
    {
        Color Grey(183,183,183);
        Forma.setFillColor(Grey);
        Apasat=true;
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
            if(!Apasat)
            {
                Forma.setFillColor(Color::White);
            }
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
            if(!Apasat)
            {
                Forma.setFillColor(Color::White);
            }
            return false;
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
    Marime TipMarime;
    Text text;
    int x,y,lungime,latime,text_dimensiune, textOfsetX,textOfsetY,IndiceValoare,FereastraID;
    void (*Functie)(void);
    bool MousePesteButon, Selectat,Apasat,Custom,Activ;
    string caleImagine;
    Buton(int pos_x, int pos_y, int lg, int lat, string txt, int dimensiune_text, int text_ofsetX, int text_ofsetY,string stringImagine,int indice_valoare,Marime tip_marime)
    {
        Activ=true;
        TipMarime=tip_marime;
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
    void SeteazaImagineButon(string cale)
    {
        textura.loadFromFile(cale);
        FormaButon.setTexture(&textura);
        caleImagine=cale;
    }
    void DeseneazaButon()
    {
        Fereastra.draw(FormaButon);
        Fereastra.draw(text);
    }
    void Muta(int x, int y)
    {
        FormaButon.setPosition(x,y);
        CreazaTextul();
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
Buton CreezaButon(int pos_x, int pos_y, int lg, int lat, string txt, int dimensiune_text, int text_ofsetX, int text_ofsetY,void(*functie)(void),string imagine,int indiceValoare,int IDfereastra,Marime tip_marime)
{
    Buton Bt(pos_x, pos_y,lg,lat,txt,dimensiune_text,text_ofsetX,text_ofsetY,imagine,indiceValoare,tip_marime);
    Bt.Functie=functie;
    Bt.FereastraID=IDfereastra;
    Butoane.push_back(Bt);
    return Bt;
}
SpatiuDestinatTextului CreeazaSpatiuPentruScris(int pos_x,int pos_y,int lg,int lat,Color Culoare,int pos_t_x,int pos_t_y,void(*functie)(void),int dim_text,string imagine,int IDfereastra)
{
    SpatiuDestinatTextului SpTxT(pos_x,pos_y,lg,lat,Culoare,pos_t_x,pos_t_y,dim_text,imagine);
    SpTxT.FereastraID=IDfereastra;
    SpTxT.Functie=functie;
    SpatiiDeScrisText.push_back(SpTxT);
    return SpTxT;
}
void DeseneazaButoane()
{
    for(int i=0; i<Butoane.size(); i++)
    {
        bool principal=(Butoane[i].FereastraID==1);
        if(Butoane[i].Activ)
        {
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
void VerificaTipulMasuriiButoanelor(int indice)
{
    if(Butoane[indice].FereastraID==1)
    {
        if(Butoane[indice].TipMarime==Bacnota)
        {
            TipMasura.setString("RON");
        }
        else if(Butoane[indice].TipMarime==Grade||Butoane[indice].TipMarime==Fahrenheit)
        {
            TipMasura.setString("Grade");
        }
        else if(Butoane[indice].TipMarime==Greutate)
        {
            TipMasura.setString("Kg");
        }
        else if(Butoane[indice].TipMarime==Lungime)
        {
            TipMasura.setString("Metri");
        }
        else if(Butoane[indice].TipMarime==Presiune)
        {
            TipMasura.setString("mmHg");
        }
        else if(Butoane[indice].TipMarime==Suprafata)
        {
            TipMasura.setString("Metri Patrati");
        }
    }
}
void InverseazaMasura(int indice);
void VerificaDacaButoaneleSuntSelectate()
{
    if(!EsteMeniul)
    {
        bool ok=false;
        for(int i=0; i<Butoane.size(); i++)
        {
            if(Butoane[i].MouseEstePeste()&&Butoane[i].Activ)
            {
                ok=true;
                VerificaTipulMasuriiButoanelor(i);
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
            if(!ok)
            {
                TipMasura.setString("");
            }
        }
    }
}
void VerificaDacaTextulEsteSelectat()
{
    if(!EsteMeniul)
    {
        for(int i=0; i<SpatiiDeScrisText.size(); i++)
        {
            if(SpatiiDeScrisText[i].MouseEstePeste())
            {
                if(Mouse::isButtonPressed(Mouse::Left)&&!SpatiiDeScrisText[i].Apasat)
                {
                    SpatiulDeTextCurentSelectat=i;
                    SpatiiDeScrisText[i].MouseClick();
                    if(SpatiiDeScrisText[i].TextScris.size()==0)
                    {
                        TText.erase(TText.begin(),TText.end());
                    }
                    else
                    {
                        TText=SpatiiDeScrisText[i].TextScris;
                    }
                }
                else if(!Mouse::isButtonPressed(Mouse::Left)&&!SpatiiDeScrisText[i].Apasat)
                {
                    SpatiiDeScrisText[i].Normal();
                }
            }
            else
            {
                if(!SpatiiDeScrisText[i].Apasat)
                {
                    SpatiiDeScrisText[i].Normal();
                }
            }
        }
    }
}
void VerificaTextIntrodusTastatura(Event event)
{
    if(!EsteMeniul)
    {
        if (event.type == Event::TextEntered)
        {
            if (event.text.unicode <=127 && SpatiulDeTextCurentSelectat>-1)
            {
                if(event.text.unicode==8&&TText.size()>0)
                {
                    TText.erase(TText.size()-1,1);
                    SpatiiDeScrisText[SpatiulDeTextCurentSelectat].TextScris=TText;
                    SpatiiDeScrisText[SpatiulDeTextCurentSelectat].ActualizeazaTextul();
                    return;
                }
                if(event.text.unicode!=8&&event.text.unicode!=13)
                {
                    TText+=static_cast<char>(event.text.unicode);
                }
                SpatiiDeScrisText[SpatiulDeTextCurentSelectat].TextScris=TText;
                SpatiiDeScrisText[SpatiulDeTextCurentSelectat].ActualizeazaTextul();
                //cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
            }
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
    bool activ=false;
    string c;
    for(int i =0 ; i<24;i++)
    {
        ConfigInput>>valoare;
        ValoriConvertor.push_back(valoare);
    }
    for(int i=0; i<4;i++)
    {
        ConfigInput>>valoare>>c>>activ;
        ValoriConvertor.push_back(valoare);
        ButonCustom ccc;
        ccc.Cale=c;
        ccc.activ=activ;
        ButoaneCustomCitite.push_back(ccc);
    }
    ConfigInput>>IndiceButonNou;
    ConfigInput.close();
    ConfigInput.clear();
}
void AfiseazaValoriConvertor()
{
    ConfigInput.open("Config.in",ios::out);
    for(int i =0; i<24; i++)
    {
        ConfigInput<<ValoriConvertor[i]<<'\n';
    }
    int j=0;
    for(int i=24;i<ValoriConvertor.size();i++)
    {
        ConfigInput<<ValoriConvertor[i]<<" "<<ButoaneCustomCitite[j].Cale<<" "<<ButoaneCustomCitite[j].activ<<'\n';
        j++;
    }
    ConfigInput<<IndiceButonNou;
    ConfigInput.close();
}
void VerificaDacaTextulIntrodusEsteCorect()
{
    string Aux;
    int c=0;
    bool ok=false;
    for(int i =0; i<TText.size(); i++)
    {
        if(TText[i]>=48&&TText[i]<=57)
        {
            Aux.push_back(TText[i]);
            c++;
            if(c>MaxCharactereTextIntrodus)
            {
                break;
            }
        }
        else if(TText[i]=='.'&&!ok)
        {
            ok=true;
            Aux.push_back(TText[i]);
            c++;
            if(c>MaxCharactereTextIntrodus)
            {
                break;
            }
        }
    }
    TText=Aux;
    if(!ok)
    {
        TText+=".0";
    }
    SpatiiDeScrisText[SpatiulDeTextCurentSelectat].TextScris=TText;
    SpatiiDeScrisText[SpatiulDeTextCurentSelectat].ActualizeazaTextul();
}
void VerificaTastaEnterCandTextulEsteIntrodus()
{
    if(SpatiulDeTextCurentSelectat>-1)
    {
        if(Keyboard::isKeyPressed(Keyboard::Return))
        {
            SpatiiDeScrisText[SpatiulDeTextCurentSelectat].CandApasamEnter();
            SpatiiDeScrisText[SpatiulDeTextCurentSelectat].Normal();
            SpatiulDeTextCurentSelectat=-1;
        }
    }
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
void DeschideFereastraDeSchimbatValoarea();
float StringToFloat(string sir);
void ClickSaModificeValoareConvertor()
{
    ValoareIntrodusa=StringToFloat(TText);
    PozitieValoareDeModificat=Butoane[IndiceButonSelectat].IndiceValoare;
    //cout<<"butonul "<<IndiceButonSelectat<<" trebuie sa modifice valoarea de pe "<<Butoane[IndiceButonSelectat].IndiceValoare<<'\n';
    if(!DeschisFereastraSchimbaValoarea)
    {
        DeschideFereastraDeSchimbatValoarea();
    }
}
string FloatToString(float nr)
{
    char cc[10];
    sprintf(cc,"%.3f",nr);
    return cc;
}
float StringToFloat(string sir)
{
    float nrFloat;
    float ajutator=1;
    float dupaVirgula=0;
    float zecimale=10;
    int dim=sir.size();
    int nrInt=0;
    int indice=0;
    while(sir[indice]!='.')
    {
        nrInt=nrInt*10+sir[indice]-48;
        indice++;
    }
    indice++;
    nrFloat=nrInt;
    while(indice<dim)
    {
        float nrr=sir[indice]-48;
        ajutator=(ajutator/zecimale)*nrr;
        dupaVirgula+=ajutator;
        ajutator=1;
        zecimale*=10;
        indice++;
    }
    nrFloat+=dupaVirgula;
    return nrFloat;
}
void Click2()
{
    cout<<"MERGEEE"<<'\n';
}
void GolesteToateSpatiileDeScrisDinFereastraSecundara()
{
    for(int i=0; i<SpatiiDeScrisText.size(); i++)
    {
        if(SpatiiDeScrisText[i].FereastraID==2)
        {
            SpatiiDeScrisText[i].Normal();
        }
    }
}
void RegulaDeTreiSimpla()
{
    for(int i=0; i<ValoriConvertor.size(); i++)
    {
        for(int i =0; i<Butoane.size(); i++)
        {
            if(Butoane[i].FereastraID==1&&Butoane[i].IndiceValoare>=0)
            {
                if(Butoane[i].TipMarime==Bacnota||Butoane[i].TipMarime==Greutate||Butoane[i].TipMarime==Lungime||Butoane[i].TipMarime==Presiune||Butoane[i].TipMarime==Dimensiune||Butoane[i].TipMarime==Suprafata)
                {
                    Butoane[i].text.setString(FloatToString(ValoriConvertor[Butoane[i].IndiceValoare]*ValoareNouaConvertor));
                }
                else if(Butoane[i].TipMarime==Grade)
                {
                    Butoane[i].text.setString(FloatToString(ValoriConvertor[Butoane[i].IndiceValoare]+ValoareNouaConvertor));
                }
                else if(Butoane[i].TipMarime==Fahrenheit)
                {
                    Butoane[i].text.setString(FloatToString(ValoareNouaConvertor*1.8+32));
                }
                //cout<<"Butonul "<<i<<" are indicele:"<<Butoane[i].IndiceValoare<<'\n';
            }
        }
    }
}
void FaCevaCandAmApasatEnterDupaCeAmIntrdusTextul()
{
    if(TText.size()>0)
    {
        VerificaDacaTextulIntrodusEsteCorect();
        ValoareNouaConvertor=StringToFloat(TText);
    }
    else
    {
        ValoareNouaConvertor=1;
    }
    RegulaDeTreiSimpla();
    cout<<ValoareNouaConvertor<<endl;
}
void DeschideFereastraDeSchimbatValoarea()
{
    IndiceButonDeModificat=IndiceButonSelectat;
    ValoarePrecedenta.setString(FloatToString(ValoriConvertor[Butoane[IndiceButonSelectat].IndiceValoare]));
    SchimbaValoarea.create(VideoMode(300,300),"Schimba Valoarea");
    DeschisFereastraSchimbaValoarea=true;
    FereastraCurentaID=2;
}
void SeteazaOValoareNouaInConvertor()
{
    VerificaDacaTextulIntrodusEsteCorect();
    ValoareNouaConvertor=StringToFloat(TText);
    ModificaValoareInConvertor(PozitieValoareDeModificat,ValoareNouaConvertor);
    ActualizeazaValorileButoanelor();
    SchimbaValoarea.close();
    DeschisFereastraSchimbaValoarea=false;
}
void SeteazaTextValoarePrecedentaConvertor()
{
    TipMasura.setFont(FontButoane);
    TipMasura.setCharacterSize(30);
    TipMasura.setFillColor(Color::Yellow);
    TipMasura.setPosition(Vector2f(180,150));
    CreeazaStaticText(3,5,30,"Valoare Precedenta:",Color::White,2);
    CreeazaStaticText(3,55,30,"Valoare Noua:",Color::White,2);
    ValoarePrecedenta.setCharacterSize(30);
    ValoarePrecedenta.setFont(FontButoane);
    ValoarePrecedenta.setFillColor(Color::Green);
    ValoarePrecedenta.setPosition(Vector2f(40,30));
}
void RotesteLogoul()
{
    IndiceLogo++;
    if(IndiceLogo>9)
    {
        IndiceLogo=0;
    }
    Logoul.setTexture(Logo[IndiceLogo]);
}
void AnimatieMeniu()
{
    if(EsteMeniul)
    {
        Meniu.setTexture(MeniuSpriteuri[IndiceMeniu]);
        IndiceMeniu++;
        if(!ApasatTastaInMeniu)
        {
            if(IndiceMeniu>21)
            {
                IndiceMeniu=1;
            }
        }
        else
        {
            if(IndiceMeniu>26)
            {
                EsteMeniul=false;
                IndiceMeniu=26;
            }
        }
    }
}
void SchimbaCuloareaFundal()
{

    timp=ceas.getElapsedTime();
    Event event;
    //cout<<timp.asSeconds()<<endl;
    if(timp.asSeconds()>=0.1)
    {
        ceas.restart();
        if(!SchimbatCuloareFundal&&!EsteMeniul)
        {
            g++;
            r++;
            b++;
            if(g>=250)
            {
                SchimbatCuloareFundal=true;
            }
        }
        else
        {
            g--;
            r--;
            b--;
            if(g<=25)
            {
                SchimbatCuloareFundal=false;
            }
        }
        if(!EsteMeniul)
        {
            RotesteLogoul();
            ImagineFundal.setColor(Color(r,g,b));
        }
        else
        {
            AnimatieMeniu();
        }
    }
}
void CitesteLogourile()
{
    Texture textur,textur2;
    Logo[0].loadFromFile("Logouri/Logo-0.png");
    Logo[1].loadFromFile("Logouri/Logo-1.png");
    Logo[2].loadFromFile("Logouri/Logo-2.png");
    Logo[3].loadFromFile("Logouri/Logo-3.png");
    Logo[4].loadFromFile("Logouri/Logo-4.png");
    Logo[5].loadFromFile("Logouri/Logo-5.png");
    Logo[6].loadFromFile("Logouri/Logo-6.png");
    Logo[7].loadFromFile("Logouri/Logo-7.png");
    Logo[8].loadFromFile("Logouri/Logo-8.png");
    Logo[9].loadFromFile("Logouri/Logo-9.png");
    Logoul.setPosition(550,20);
    Logoul.scale(0.07,0.07);
    MeniuSpriteuri[1].loadFromFile("Meniu/Meniu_1.png");
    MeniuSpriteuri[2].loadFromFile("Meniu/Meniu_2.png");
    MeniuSpriteuri[3].loadFromFile("Meniu/Meniu_3.png");
    MeniuSpriteuri[4].loadFromFile("Meniu/Meniu_4.png");
    MeniuSpriteuri[5].loadFromFile("Meniu/Meniu_5.png");
    MeniuSpriteuri[6].loadFromFile("Meniu/Meniu_6.png");
    MeniuSpriteuri[7].loadFromFile("Meniu/Meniu_7.png");
    MeniuSpriteuri[8].loadFromFile("Meniu/Meniu_8.png");
    MeniuSpriteuri[9].loadFromFile("Meniu/Meniu_9.png");
    MeniuSpriteuri[10].loadFromFile("Meniu/Meniu_10.png");
    MeniuSpriteuri[11].loadFromFile("Meniu/Meniu_11.png");
    MeniuSpriteuri[12].loadFromFile("Meniu/Meniu_12.png");
    MeniuSpriteuri[13].loadFromFile("Meniu/Meniu_13.png");
    MeniuSpriteuri[14].loadFromFile("Meniu/Meniu_14.png");
    MeniuSpriteuri[15].loadFromFile("Meniu/Meniu_15.png");
    MeniuSpriteuri[16].loadFromFile("Meniu/Meniu_16.png");
    MeniuSpriteuri[17].loadFromFile("Meniu/Meniu_17.png");
    MeniuSpriteuri[18].loadFromFile("Meniu/Meniu_18.png");
    MeniuSpriteuri[19].loadFromFile("Meniu/Meniu_19.png");
    MeniuSpriteuri[20].loadFromFile("Meniu/Meniu_20.png");
    MeniuSpriteuri[21].loadFromFile("Meniu/Meniu_21.png");
    MeniuSpriteuri[22].loadFromFile("Meniu/Meniu_22.png");
    MeniuSpriteuri[23].loadFromFile("Meniu/Meniu_23.png");
    MeniuSpriteuri[24].loadFromFile("Meniu/Meniu_24.png");
    MeniuSpriteuri[25].loadFromFile("Meniu/Meniu_25.png");
    MeniuSpriteuri[26].loadFromFile("Meniu/Meniu_26.png");
    Meniu.setPosition(0,0);
    Meniu.setTexture(MeniuSpriteuri[1]);
    Meniu.scale(0.823,0.74);
}
void CreeazaButoanePersonalizabile()
{
    if(IndiceButonDeAdaugare+IndiceButonNou<28)
    {
        string c="butoane/Custom/";
        cout<<IndiceButonDeAdaugare+IndiceButonNou<<endl;
        Butoane[IndiceButonDeAdaugare+IndiceButonNou].SeteazaImagineButon(c+TText);
        Butoane[IndiceButonDeAdaugare+IndiceButonNou].Activ=true;
        ButoaneCustomCitite[IndiceButonNou].Cale=c+TText;
        ButoaneCustomCitite[IndiceButonNou].activ=true;
        IndiceButonNou++;
    }
}
void StergeButon()
{
    if(IndiceButonNou<=0)
    {
        return;
    }
    for(int i=Butoane.size()-1;i>=0;i--)
    {
        if(Butoane[i].Custom&&Butoane[i].Activ)
        {
            Butoane[i].Activ=false;
            IndiceButonNou--;
            ButoaneCustomCitite[IndiceButonNou].activ=false;
            return;
        }
    }
}
int main()
{
    FontButoane.loadFromFile("BALLSONTHERAMPAGE.ttf");
    ImgFundal.loadFromFile("imagine_fundal.png");
    ImagineFundal.setTexture(ImgFundal);
    CitesteValoriConvertor();
    ImagineFundal.setScale(Vector2f(0.9,.8));
    Buton B_Euro=CreezaButon(10,200, 200,70,"0.000",30,10,0,ClickSaModificeValoareConvertor,"butoane/Valute/buton_euro.png",0,1,Bacnota);
    Buton B_Dolar=CreezaButon(220,200, 200,70,"0.000",30,10,0,ClickSaModificeValoareConvertor,"butoane/Valute/buton_dolar.png",1,1,Bacnota);
    Buton B_LiraSterlina=CreezaButon(430,200, 200,70,"0.000",30,10,0,ClickSaModificeValoareConvertor,"butoane/Valute/buton_lira.png",2,1,Bacnota);
    Buton B_FrancElvetian=CreezaButon(640,200, 200,70,"0.000",30,10,0,ClickSaModificeValoareConvertor,"butoane/Valute/buton_franc.png",3,1,Bacnota);
    Buton B_Celsius=CreezaButon(10,285, 200,70,"0.000",30,10,0,ClickSaModificeValoareConvertor,"butoane/Grade/buton_celsius.jpg",4,1,Grade);
    Buton B_Kelvin=CreezaButon(220,285, 200, 70, "0.000", 30, 10, 0, ClickSaModificeValoareConvertor, "butoane/Grade/buton_kelvin.jpg", 5, 1, Grade);
    Buton B_Fahrenheit=CreezaButon(430, 285, 200, 70, "0.000", 30, 10, 0, ClickSaModificeValoareConvertor, "butoane/Grade/buton_fahrenheit.jpg", 6, 1, Fahrenheit);
    Buton B_Rankine=CreezaButon(640, 285, 200, 70, "0.000", 30, 10, 0, ClickSaModificeValoareConvertor, "butoane/Grade/buton_rankine.jpg", 7, 1, Grade);
    Buton B_Pounds=CreezaButon(10, 370, 200, 70, "0.000", 30, 10, 0, ClickSaModificeValoareConvertor, "butoane/Greutate/buton_pounds.jpg", 8, 1, Greutate);
    Buton B_Carats=CreezaButon(220, 370, 200, 70, "0.000", 30, 10, 0, ClickSaModificeValoareConvertor, "butoane/Greutate/buton_carats.jpg", 9, 1, Greutate);
    Buton B_Ounces=CreezaButon(430, 370, 200, 70, "0.000", 30, 10, 0, ClickSaModificeValoareConvertor, "butoane/Greutate/buton_ounces.jpg", 10, 1, Greutate);
    Buton B_Stone=CreezaButon(640, 370, 200, 70, "0.000", 30, 10, 0, ClickSaModificeValoareConvertor, "butoane/Greutate/buton_stone.jpg", 11, 1, Greutate);
    Buton B_Feet=CreezaButon(10, 455, 200, 70, "0.000", 30, 10, 0, ClickSaModificeValoareConvertor, "butoane/Lungimi/buton_feet.jpg", 12, 1, Lungime);
    Buton B_Miles=CreezaButon(220, 455, 200, 70, "0.000", 30, 10, 0, ClickSaModificeValoareConvertor, "butoane/Lungimi/buton_miles.jpg", 13, 1, Lungime);
    Buton B_Inch=CreezaButon(430, 455, 200, 70, "0.000", 30, 10, 0, ClickSaModificeValoareConvertor, "butoane/Lungimi/buton_inch.jpg", 14, 1, Lungime);
    Buton B_Yards=CreezaButon(640, 455, 200, 70, "0.000", 30, 10, 0, ClickSaModificeValoareConvertor, "butoane/Lungimi/buton_yards.jpg", 15, 1, Lungime);
    Buton B_Atmosfere=CreezaButon(10, 540, 200, 70, "0.000", 30, 10, 0, ClickSaModificeValoareConvertor, "butoane/Presiune/buton_atmosfere.jpg", 16, 1, Presiune);
    Buton B_Bari=CreezaButon(220, 540, 200, 70, "0.000", 30, 10, 0, ClickSaModificeValoareConvertor, "butoane/Presiune/buton_bari.jpg", 17, 1, Presiune);
    Buton B_Pascali=CreezaButon(430, 540, 200, 70, "0.000", 30, 10, 0, ClickSaModificeValoareConvertor, "butoane/Presiune/buton_pascali.jpg", 18, 1, Presiune);
    Buton B_Psi=CreezaButon(640, 540, 200, 70, "0.000", 30, 10, 0, ClickSaModificeValoareConvertor, "butoane/Presiune/buton_poundspersquareinch.jpg", 19, 1, Presiune);
    Buton B_Acres=CreezaButon(10, 625, 200, 70, "0.000", 30, 10, 0, ClickSaModificeValoareConvertor, "butoane/Suprafata/buton_acres.jpg", 20, 1, Suprafata);
    Buton B_Hectare=CreezaButon(220, 625, 200, 70, "0.000", 30, 10, 0, ClickSaModificeValoareConvertor, "butoane/Suprafata/buton_hectare.jpg", 21, 1, Suprafata);
    Buton B_Sf=CreezaButon(430, 625, 200, 70, "0.000", 30, 10, 0, ClickSaModificeValoareConvertor, "butoane/Suprafata/buton_square_feet.jpg", 22, 1, Suprafata);
    Buton B_Sy=CreezaButon(640, 625, 200, 70, "0.000", 30, 10, 0, ClickSaModificeValoareConvertor, "butoane/Suprafata/buton_square_yards.jpg", 23, 1, Suprafata);
    Buton Custom1=CreezaButon(10,710,200,70,"0.000",30,10,0,ClickSaModificeValoareConvertor,ButoaneCustomCitite[0].Cale,24,1,Suprafata);
    Butoane[Butoane.size()-1].Activ=ButoaneCustomCitite[0].activ;
    Butoane[Butoane.size()-1].Custom=true;
    Buton Custom2=CreezaButon(220,710,200,70,"0.000",30,10,0,ClickSaModificeValoareConvertor,ButoaneCustomCitite[1].Cale,25,1,Suprafata);
    Butoane[Butoane.size()-1].Activ=ButoaneCustomCitite[1].activ;
    Butoane[Butoane.size()-1].Custom=true;
    Buton Custom3=CreezaButon(430,710,200,70,"0.000",30,10,0,ClickSaModificeValoareConvertor,ButoaneCustomCitite[2].Cale,26,1,Suprafata);
    Butoane[Butoane.size()-1].Activ=ButoaneCustomCitite[2].activ;
    Butoane[Butoane.size()-1].Custom=true;
    Buton Custom4=CreezaButon(640,710,200,70,"0.000",30,10,0,ClickSaModificeValoareConvertor,ButoaneCustomCitite[3].Cale,27,1,Suprafata);
    Butoane[Butoane.size()-1].Activ=ButoaneCustomCitite[3].activ;
    Butoane[Butoane.size()-1].Custom=true;
    Buton StergeButonul=CreezaButon(700, 150, 40, 40, "", 30, 10, 0, StergeButon, "butoane/Gunoi.png", -1, 1, FaraMasura);
    SpatiuDestinatTextului TextPtValoriDeIntrodus=CreeazaSpatiuPentruScris(10, 150,250,40,Color::Blue,20,0,FaCevaCandAmApasatEnterDupaCeAmIntrdusTextul,33,"butoane/LocScris_imagine.png",1);
    SpatiuDestinatTextului ValoriPtCaleImagine=CreeazaSpatiuPentruScris(400, 150,300,40,Color::Blue,20,0,CreeazaButoanePersonalizabile,33,"butoane/LocScris_imagine.png",1);
    SpatiuDestinatTextului ValoareNouaIntrodusaMarime=CreeazaSpatiuPentruScris(3,85,250,30,Color::Blue,5,-5,SeteazaOValoareNouaInConvertor,30,"butoane/LocScris_imagine.png",2);
    CreeazaStaticText(30,117,35,"Valoare:",Color::White,1);
    CreeazaStaticText(250,1,80,"Converter",Color::White,1);
    CreeazaStaticText(450,117,35,"Masura noua:",Color::White,1);
    Fereastra.create(VideoMode(840,800),"Converter");
    SeteazaTextValoarePrecedentaConvertor();
    ActualizeazaValorileButoanelor();
    CitesteLogourile();
    while (Fereastra.isOpen())
    {
        //cout<<IndiceButonSelectat<<endl;
        SchimbaCuloareaFundal();
        PozitieMouse=Mouse::getPosition(Fereastra);
        Event event;
        while (Fereastra.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                Fereastra.close();
            }
            if(event.type==Event::KeyPressed&&EsteMeniul)
            {
                ApasatTastaInMeniu=true;
                IndiceMeniu=21;
            }
            VerificaTextIntrodusTastatura(event);
        }
        Fereastra.clear();
        VerificaDacaButoaneleSuntSelectate();
        VerificaDacaTextulEsteSelectat();
        VerificaTastaEnterCandTextulEsteIntrodus();
        Fereastra.draw(ImagineFundal);
        DeseneazaButoane();
        DeseneazaSpatiiScris();
        DeseneazaTexteleStatice();
        Fereastra.draw(TipMasura);
        Fereastra.draw(Logoul);
        if(EsteMeniul)
        {
            Fereastra.draw(Meniu);
        }
        Fereastra.display();
        while(SchimbaValoarea.isOpen())
        {
            //cout<<IndiceButonSelectat<<endl;
            SchimbaCuloareaFundal();
            PozitieMouse=Mouse::getPosition(SchimbaValoarea);
            Event event2;
            while (SchimbaValoarea.pollEvent(event2))
            {
                if (event2.type == Event::Closed)
                {
                    DeschisFereastraSchimbaValoarea=false;
                    FereastraCurentaID=1;
                    GolesteToateSpatiileDeScrisDinFereastraSecundara();
                    IndiceButonSelectat=-1;
                    SchimbaValoarea.close();
                }
                VerificaTextIntrodusTastatura(event2);
            }
            SchimbaValoarea.clear();
            VerificaDacaButoaneleSuntSelectate();
            VerificaDacaTextulEsteSelectat();
            VerificaTastaEnterCandTextulEsteIntrodus();
            SchimbaValoarea.draw(ImagineFundal);
            DeseneazaButoane();
            DeseneazaSpatiiScris();
            SchimbaValoarea.draw(ValoarePrecedenta);
            DeseneazaTexteleStatice();
            SchimbaValoarea.display();
        }
    }
    for(int i=25; i<Butoane.size();i++)
    {
        cout<<Butoane[i].caleImagine<<endl;
    }
    AfiseazaValoriConvertor();
    return 0;
}
