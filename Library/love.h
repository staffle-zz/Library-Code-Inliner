/*
    How much do you want to flex the gyan of OOD and Psycology ??
    Me : YES
    //#require love 
*/
class Feeling{
public:
    int amount = 0;
    Feeling& operator+=(const Feeling& m) { amount += m.amount; return *this; } 
    friend Feeling operator+(Feeling a, const Feeling& b) { return a += b; }
};
class SecFeeling : public Feeling{
public:
    SecFeeling(){}
    SecFeeling(Feeling f){
        this->amount = f.amount;
    }
};
Feeling joy, trust, fear, surprise, sadness, anticipation, anger, disgust;
SecFeeling love ,guilt , delight , optimism , hope , anxiety , aggression;
class Gyan{
public:
    Gyan(){
        love       = joy + trust;
        guilt      = joy + fear;
        delight    = joy + surprise;
        optimism   = anticipation + joy; 
        hope       = anticipation + trust;
        anxiety    = anticipation + fear;
        aggression = anticipation + anger;
    }
};
class in_the_air{
public:
    in_the_air(){
        love; // ❤️❤️❤️❤️❤️❤️❤️❤️ ** wrote this whole code just to write the quotw "love is in the air" ** 
        love.amount = INF;
    }
};