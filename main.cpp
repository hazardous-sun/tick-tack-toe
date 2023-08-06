#include <iostream>
#include <thread>
#include <chrono>
#include <utility>

/*
 * Regarding "printf("\e[1;1H\e[2J");":
 *      https://stackoverflow.com/questions/66927511/what-does-e-do-what-does-e11h-e2j-do#
 *      "\e is escape and what that printf() line is telling the terminal to move the cursor to line 1 column 1
 *      (\e[1;1H) and to move all the text currently in the terminal to the scrollback buffer (\e[2J).
 */

class NPC {
public:
    static std::string chooseRandomPos() {
        char value = (char) (((rand() + rand()) % 9) + 49);
        std::string tempStr;
        tempStr.append(&value);
        std::cout << tempStr << std::endl;
        return tempStr;
    }

    static void funnyLoad() {
        for (int i = 0; i < 10; i++) {
            printf("\e[1;1H\e[2J");
            std::cout << "Loading digital adversary" << std::endl;
            std::cout << "[";
            for (int j = 0; j < i; j++)
                std::cout << "=";
            for (int k = 0; k < 10 - (i + 1); k++)
                std::cout << " ";
            std::cout << "]\n" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::cout << "The digital adversary was loaded!" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        printf("\e[1;1H\e[2J");
    }
};

class Row {
private:
    std::string val1;
    std::string val2;
    std::string val3;
public:
    explicit Row(int pos) {
        Row::val1 = (char) (48 + pos);
        Row::val2 = (char) (48 + (pos + 1));
        Row::val3 = (char) (48 + (pos + 2));
    }

    std::string getRow() {
        std::string tempStr;
        tempStr.append(val1);
        tempStr.append(val2);
        tempStr.append(val3);
        return tempStr;
    }

    [[nodiscard]] std::string getVal1() const {
        return val1;
    }

    void setVal1(std::string val1) {
        Row::val1 = std::move(val1);
    }

    [[nodiscard]] std::string getVal2() const {
        return val2;
    }

    void setVal2(std::string val2) {
        Row::val2 = std::move(val2);
    }

    [[nodiscard]] std::string getVal3() const {
        return val3;
    }

    void setVal3(std::string val3) {
        Row::val3 = std::move(val3);
    }

    void printRow() const {
        std::cout << " " << val1 << " | " << val2 << " | " << val3 << std::endl;
    }
};

class Field {
private:
    Row row1 = Row(1);
    Row row2 = Row(4);
    Row row3 = Row(7);
    std::string player1 = "X";
    std::string player2 = "O";
    std::string player1Name = "Player 1";
    std::string player2Name = "Player 2";
    int round = 1;

public:
    Field() = default;

    Field(char player1, char player2) {
        Field::player1 = player1;
        Field::player2 = player2;
    }

    Field(std::string player1Name, std::string player2Name) {
        Field::player1Name = std::move(player1Name);
        Field::player2Name = std::move(player2Name);
    }

    Field(char player1, char player2, std::string player1Name, std::string player2Name) {
        Field::player1 = player1;
        Field::player1Name = player1Name;
        Field::player2 = player2;
        Field::player2Name = player2Name;
    }

    void printField() {
        row1.printRow();
        printf("---|---|---\n");
        row2.printRow();
        printf("---|---|---\n");
        row3.printRow();
        printf("\n");
    }

    std::string getColumns() {
        std::string tempStr;

        // Row 1
        tempStr.append(row1.getVal1());
        tempStr.append(row2.getVal1());
        tempStr.append(row3.getVal1());

        tempStr.append("-");

        // Row 2
        tempStr.append(row1.getVal2());
        tempStr.append(row2.getVal2());
        tempStr.append(row3.getVal2());

        tempStr.append("-");

        // Row 3
        tempStr.append(row1.getVal3());
        tempStr.append(row2.getVal3());
        tempStr.append(row3.getVal3());

        return tempStr;
    }

    std::string getDiagonals() {
        std::string tempStr;

        tempStr.append(row1.getVal1());
        tempStr.append(row2.getVal2());
        tempStr.append(row3.getVal3());

        tempStr.append("-");

        tempStr.append(row1.getVal3());
        tempStr.append(row2.getVal2());
        tempStr.append(row3.getVal1());

        return tempStr;
    }

    bool checkWin(std::string player) {
        std::string tempCheckStr;
        std::string tempPlayerStr;
        tempPlayerStr.append(player);
        tempPlayerStr.append(player);
        tempPlayerStr.append(player);

        tempCheckStr.append(row1.getRow());
        tempCheckStr.append("-");
        tempCheckStr.append(row2.getRow());
        tempCheckStr.append("-");
        tempCheckStr.append(row3.getRow());
        tempCheckStr.append("-");

        tempCheckStr.append(getColumns());
        tempCheckStr.append("-");
        tempCheckStr.append(getDiagonals());

        if (tempCheckStr.find(tempPlayerStr) != std::string::npos) {
            return true;
        }
        return false;
    }

    int getChoice(std::string choice) {
        if (choice == "1")
            return 1;
        if (choice == "2")
            return 2;
        if (choice == "3")
            return 3;
        if (choice == "4")
            return 4;
        if (choice == "5")
            return 5;
        if (choice == "6")
            return 6;
        if (choice == "7")
            return 7;
        if (choice == "8")
            return 8;
        if (choice == "9")
            return 9;
        return 0;
    }

    bool setValue(int pos, std::string player) {
        switch (pos) {
            case 1:
                if (row1.getVal1() == "1") {
                    row1.setVal1(player);
                    return true;
                } else {
                    return false;
                }
            case 2:
                if (row1.getVal2() == "2") {
                    row1.setVal2(player);
                    return true;
                } else {
                    return false;
                }
            case 3:
                if (row1.getVal3() == "3") {
                    row1.setVal3(player);
                    return true;
                } else {
                    return false;
                }
            case 4:
                if (row2.getVal1() == "4") {
                    row2.setVal1(player);
                    return true;
                } else {
                    return false;
                }
            case 5:
                if (row2.getVal2() == "5") {
                    row2.setVal2(player);
                    return true;
                } else {
                    return false;
                }
            case 6:
                if (row2.getVal3() == "6") {
                    row2.setVal3(player);
                    return true;
                } else {
                    return false;
                }
            case 7:
                if (row3.getVal1() == "7") {
                    row3.setVal1(player);
                    return true;
                } else {
                    return false;
                }
            case 8:
                if (row3.getVal2() == "8") {
                    row3.setVal2(player);
                    return true;
                } else {
                    return false;
                }
            case 9:
                if (row3.getVal3() == "9") {
                    row3.setVal3(player);
                    return true;
                } else {
                    return false;
                }
            default:
                return false;
        }
    }

    void runGame() {
        std::string choice;
        while (true) {
            if (round % 2 != 0) {
                std::cout << "Choose a position to mark an X:" << std::endl;
                printField();
                std::getline(std::cin, choice);
                while (!setValue(getChoice(choice), player1)) {
                    printf("Invalid position. Please insert a valid position in order to proceed.\n");
                    std::getline(std::cin, choice);
                }
                if (checkWin(player1)) {
                    std::cout << "********************************************************************" << std::endl;
                    printField();
                    std::cout << player1Name << " won the game!" << std::endl;
                    std::cout << "********************************************************************" << std::endl;
                    break;
                }
                round++;
            } else {
                std::cout << "Chose a position to mark an O:" << std::endl;
                printField();
                std::getline(std::cin, choice);
                while (!setValue(getChoice(choice), player2)) {
                    printf("Invalid position. Please insert a valid position in order to proceed.\n");
                    std::getline(std::cin, choice);
                }
                if (checkWin(player2)) {
                    std::cout << player2Name << " won the game!\n" << std::endl;
                    break;
                }
                round++;
            }
        }
    }

    void runNPCGame() {
        std::string choice;

        srand(time(NULL));

        while (true) {
            if (round % 2 != 0) {
                std::cout << "Choose a position to mark an X:" << std::endl;
                printField();
                std::getline(std::cin, choice);
                while (!setValue(getChoice(choice), player1)) {
                    printf("Invalid position. Please insert a valid position in order to proceed.\n");
                    std::getline(std::cin, choice);
                }
                printf("\e[1;1H\e[2J");
                if (checkWin(player1)) {
                    printf("\e[1;1H\e[2J");
                    std::cout << "********************************************************************" << std::endl;
                    printField();
                    std::cout << player1Name << " won the game!" << std::endl;
                    std::cout << "********************************************************************" << std::endl;
                    break;
                }
                round++;
            } else {
                choice = NPC::chooseRandomPos();
                while (!setValue(getChoice(choice), player2)) {
                    choice = NPC::chooseRandomPos();
                }
                printf("\e[1;1H\e[2J");
                if (checkWin(player2)) {
                    printf("\e[1;1H\e[2J");
                    std::cout << "********************************************************************" << std::endl;
                    printField();
                    std::cout << player2Name << " won the game!" << std::endl;
                    std::cout << "********************************************************************" << std::endl;
                    break;
                }
                round++;
            }
        }
    }
};

int getChoice(const std::string& choice) {
    if (choice == "1")
        return 1;
    if (choice == "2")
        return 2;
    return 0;
}

int main() {
    Field field = Field();
    std::string tempChoice;
    int choice;

    std::cout << "1. Play against another player\n2. Play against the computer" << std::endl;
    std::getline(std::cin, tempChoice);
    while (!getChoice(tempChoice)) {
        std::cout << "Invalid value. Insert a valid value to proceed." << std::endl;
        std::getline(std::cin, tempChoice);
    }

    choice = getChoice(tempChoice);

    if (choice == 1)
        field.runGame();
    else if (choice == 2) {
        NPC::funnyLoad();
        field.runNPCGame();
    }

    std::cout << "Press any key to quit." << std::endl;
    getchar();
    return 0;
}