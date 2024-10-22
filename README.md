
# GPT-3.5-turbo Text Adventure







[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)
[![version](https://img.shields.io/badge/version-1.0.0-blue)]()
[![language](https://img.shields.io/badge/-c++-black?logo=c%2B%2B&style=social)](https://isocpp.org/)



## A context focused no frills OpenAI API implementation 

This game uses the GPT-3.5-turbo model to process actions and develop a story based on it.
The OpenAI API typically only has a 2,000 word limit, so after a certain length, the AI will be prompted to summarize the game. This then is fed back into the AI again and feasibly makes the game infinite. The token exchange rate is based on the selected model which may change, or be upgraded in the future. Additionally the model parameters are preset based on tweaking and testing on my side, but they may be modified to your liking in the json payload setup section of the code.

## Dependencies

-Curl Library

-OpenaAI C++ Library by coin-au-carre and U-K-L
## Potential Issues


-Setting description messes up AI response.

The setting should be described in the third person with proper english formatting and a period at the end. This helps the AI understand what you want, and better act as a text adventure game.

-Built for windows.

Some commands are used as they specify for windows like cls.

-Possibility of overspending tokens

If the user input is too long or the AI responds in an unforseen manner the program may spend more tokens then you have allotted. Use the API usage website to set harder limits.




## Github for OpenAI C++ Library

[OpenAI.cpp](https://github.com/olrea/openai-cpp)


## License

[MIT](https://choosealicense.com/licenses/mit/)

