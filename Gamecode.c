#include "openai.hpp"
#include <iostream>
using namespace std;
using json = nlohmann::json;
int main() {
    // Initialize variables
    double money = 0, tok = 0;
    int savestate = 0;
    int toke = 0;
    int first = 0;
    std::string loc;
    std::string prev_AI_res = "";
    std::string key = "";
    system("cls");
    // Print welcome message
    cout << "Welcome to the GPT-3 Text Adventure Game!" <<endl;
    cout << "This game is a text adventure game that uses GPT-3 to generate the story and respond to your commands." <<endl;
    cout << "You will be given a prompt and you will type in your command. The game will then respond to your command." <<endl;
    cout << "To start type how much money you want to spend on the game. The more money you spend the better the game will be." <<endl;
    cout << "The game will end when you escape the house." <<endl;
    cout << "Type dollar amount: $";
    cin >> money;
    // Check if user has enough money to play the game
    if (money == 0) {
        cout << "You don't have enough money to play the game." <<endl;
        return 0;
    }
    else if (money > 100) {
        cout << "You have spent too much money on the the api." <<endl;
        return 0;
    }
    else {
        tok = money/0.000002;
        cout << "You have " << tok << " tokens to spend on the game." <<endl;
        cout << "Enter OpenAI API key (Do not share this key with anyone): "<<endl;
        cin >> key;
        openai::start(key);
    
    }
    // Get setting information from user
    std::cout << "Enter starting location sentences: ";
    std::cin.ignore();
    while (loc.empty()) {
    std::getline(std::cin, loc);
    }  
    // Prep player input for AI with proper context
    std::string content = "";
    std::string context = "I want you to act as a Text Adventure game, and I want you to only reply with the game output inside one unique code block, and nothing else. This will be a moderately challenging game and some choices can lead to instant death, but I can always re-do the last fatal choice to continue the game if I want to. I will type commands and dialog, and you will only reply with what the text adventure game would show. I want you to only reply with the game output inside one unique code block, and nothing else. The game should always show one screen, and always wait for me to enter the next command. The game should always show \"health\", \"location\", \"description\", and \"inventory\". Do not write explanations. Do not type commands unless I instruct you to do so. It is imperative that these rules are followed without exception. I can do whatever I want that is based on the possible commands and the story never ends. I can attack any character in the story and other characters will respond realistically, depending on their relationship to the character and/or the context of the events itself. The player starts with four random realistic to the setting items in their inventory. If the player dies put 'GAME OVER' in the response. Setting: ";
    context += loc;
    std::string input;
    // Loop until GAME OVER is found in AI response
    while (true) {
        retry:
        input= "";
        savestate = 0;
        // Handle case where user has no tokens left
        if(tok <= toke) {
            std::string mor_tok;
            cout << "You have run out of tokens." <<endl;
            cout << "Would you like to buy more tokens? (y/n)" <<endl;
            cin >> mor_tok;
            if(mor_tok == "y") {
                cout << "How much money would you like to spend on tokens?" <<endl;
                cout << "Type dollar amount: $" <<endl;
                cin >> money;
                tok = money/0.000002;
                cout << "You have " << tok << " tokens to spend on the game." <<endl;
            }
            else {
                cout << "You have chosen to end the game." <<endl;
                break;
            }
            
        }
        // Skips on first iteration and when AI needs to summarize game
        if(first != 0 && std::count(context.begin(), context.end(), ' ') <= 800){

        // Get user input
        std::cout << "Enter input must start with 'I': " << std::endl;
        std::cin.ignore();
        while(input.empty()) {
        std::getline(std::cin, input);
        // Input added to content string
        content = context + " Player: " + input;
        }
        }
        else {
            // Context is directly placed in content on the first iteration
            content = context;
        }
        if (std::count(context.begin(), context.end(), ' ') > 800) {
        // Prompt AI to summarize text adventure game and reset content string
        std::string save = "Summarize the following text adventure game into a save state you will remember in a different conversation in less then 500 words without using the term 'GAME OVER'.";
        // Parse context to erase unnecessary information
        context.erase(context.find("I want you to act as a Text Adventure game, and I want you to only reply with the game output inside one unique code block, and nothing else. This will be a moderately challenging game and some choices can lead to instant death, but I can always re-do the last fatal choice to continue the game if I want to. I will type commands and dialog, and you will only reply with what the text adventure game would show. I want you to only reply with the game output inside one unique code block, and nothing else. The game should always show one screen, and always wait for me to enter the next command. The game should always show \"health\", \"location\", \"description\", and \"inventory\". Do not write explanations. Do not type commands unless I instruct you to do so. It is imperative that these rules are followed without exception. I can do whatever I want that is based on the possible commands and the story never ends. I can attack any character in the story and other characters will respond realistically, depending on their relationship to the character and/or the context of the events itself. The player starts with four random realistic to the setting items in their inventory. If the player dies put 'GAME OVER' in the response."), 0) ;
        content = save + context;
        context = "I want you to act as a Text Adventure game, and I want you to only reply with the game output inside one unique code block, and nothing else. This will be a moderately challenging game and some choices can lead to instant death, but I can always re-do the last fatal choice to continue the game if I want to. I will type commands and dialog, and you will only reply with what the text adventure game would show. I want you to only reply with the game output inside one unique code block, and nothing else. The game should always show one screen, and always wait for me to enter the next command. The game should always show \"health\", \"location\", \"description\", and \"inventory\". Do not write explanations. Do not type commands unless I instruct you to do so. It is imperative that these rules are followed without exception. I can do whatever I want that is based on the possible commands and the story never ends. I can attack any character in the story and other characters will respond realistically, depending on their relationship to the character and/or the context of the events itself. The player starts with four random realistic to the setting items in their inventory. If the player dies put 'GAME OVER' in the response. Setting: ";
        context += loc;
        savestate = 1;
        }
        // Set up the API data payload
        cout << "Loading... Please wait." <<endl;
        
       json chat_json;
        json messages_array = json::array();
        json messages_object = json::object();

        messages_object["role"] = "user";
        messages_object["content"] = content;
        messages_array.emplace_back(messages_object);

        chat_json["model"] = "gpt-3.5-turbo";
        chat_json["messages"] = messages_array;
        chat_json["stop"] = "Player:";
        chat_json["frequency_penalty"] = 0.6;
        chat_json["temperature"] = 0;
        auto chat = openai::chat().create(chat_json);
        // Parse the AI response
        first++;
        auto choices = chat["choices"];
        auto message = choices[0]["message"];

        std::string stop_rsn = choices[0]["finish_reason"];
        std::string AI_res = message["content"];
        // Check if AI response is valid before printing
        if (stop_rsn == "stop") {
            toke = chat["usage"]["total_tokens"].get<int>();
            tok -= toke;
            
            if (savestate == 0){
            cout << "\n" << AI_res << endl;
            cout << "Tokens left: " << tok << endl;
            context = content;
            prev_AI_res = AI_res;
            context += AI_res;}
            // Handle case when AI needs to summarize game
            else {
                cout << "The AI has summarized the game." <<endl;
                context += AI_res;
                context += " Last action: ";
                context += prev_AI_res;
            }
            }
        else{
            // Handle case when AI can't generate more
            cout << "The AI really didn't understand youre query, try again." <<endl;
            goto retry;
            }
            // Terminate loop if GAME OVER is found in AI response
        if (AI_res.find("GAME OVER") != string::npos) {
                break; }
}
}