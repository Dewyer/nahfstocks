## NAHFSTOCK

- Exchange
    - works in cycles = 1sec

    - Auction Market like the NYSE
        - Bids and asks are submitted for each second
        - If matching pairs are submitted, execute them
        - Random system determines order priority

    - Sim starts with IPO-s
    - and at the end of a fiscal quarter

- Company
    - Has hidden values
    - sector is on a spectrum
    - Okay meter - bad news decrase it, when its zero company goes bankrupt
    - Risk - higher value creates bigger events
    - Earnings offset - cycle offset to the fiscal quarter
        - after the first
    - Leadership bias


- Event
    - indicate changes in market conditions
    - Event props:
        - Target: Global, Sector, Individual Company
        - Weight: Wrapped exponential distribution - how big the news is
        - Nonce: TraderAgent interpretation modifier
        - General Sentiment: Good news or bad news ?
    - Random events
        - Have different probabilities to occur
    - Reoccuring events:
        - Earnings call
            - has fix weight and is individual
            - Nonce is fix as well
            - Senitment is the result compared to expectations

- TraderAgent
    - Creates orders on the exchange
    - Has biases
    - Reacts to incoming events
    - Reaction time is in the bias es well - but is random withing a range - normal dist centered on point
    - Has an initial money pool
