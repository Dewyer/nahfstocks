## Trader Ideas

- Trader settings:
    - Loves Finances
    - Loves leadership
    - Sector focus
    - Sector threshold
    - Volume sensitivity
    - Price sensitivity
    - Stop loss sentiment
    - Fundamental stop loss sentiment bonus
    - Imd. reinvestment percentage
    
    
- has N positions he wishes to maintain
- Sentiment
    - Fundamental sentiment algorithm based on basics
        - Company data 
    - Events change sentiment
    - Market orders / price changes sentiment
        - Lot of buys increase sell decrase
- Triggers
    - They initially buy N stocks
    - Ammount is 1/N +- 10%
    - Sell trigger:
        - Moving avg. sentiment dips to a set level + the % of the fundamental according to bonus
    - Buy:
        - If they can buy they will look for one good op. at random and buy that
    - Income reinvestment:
        - How much do they hold for the next buy / how much they put in to their best plays
    

Negotioations:

Sell: ask + %

wantness ? = |sentiment| + time

buy: bid - %