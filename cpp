#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class Question {
public:
    Question(const std::string& question, const std::vector<std::string>& choices, char correctAnswer)
        : question(question), choices(choices), correctAnswer(correctAnswer) {}

    const std::string& getQuestion() const {
        return question;
    }

    const std::vector<std::string>& getChoices() const {
        return choices;
    }

    char getCorrectAnswer() const {
        return correctAnswer;
    }

private:
    std::string question;
    std::vector<std::string> choices;
    char correctAnswer;
};

class Quiz {
public:
    void addQuestion(const Question& question) {
        questions.push_back(question);
    }

    void startQuiz() {
        std::cout << "Hoş geldiniz! Bilgi yarışmamıza başlayalım." << std::endl;

        int score = 0;
        for (const auto& question : questions) {
            askQuestion(question);
            char userAnswer = getUserAnswer();
            if (userAnswer == question.getCorrectAnswer()) {
                std::cout << "Doğru!\n";
                score++;
            }
            else {
                std::cout << "Yanlış. Doğru cevap: " << question.getCorrectAnswer() << "\n";
            }
            std::cout << "-----------------------------\n";
        }

        std::cout << "Bilgi yarışmamız sona erdi. Toplam puanınız: " << score << " / " << questions.size() << "\n";
    }

private:
    std::vector<Question> questions;

    void askQuestion(const Question& question) const {
        std::cout << "Soru: " << question.getQuestion() << "\n";
        const auto& choices = question.getChoices();
        for (size_t i = 0; i < choices.size(); ++i) {
            std::cout << static_cast<char>('A' + i) << ") " << choices[i] << "\n";
        }
    }

    char getUserAnswer() const {
        char userAnswer;
        std::cout << "Cevabınızı girin (A, B, C, D): ";
        std::cin >> userAnswer;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Satır sonu karakterini temizle
        return std::toupper(userAnswer);
    }
};

int main() {
    setlocale(LC_ALL, "Turkish");
    Quiz quiz;

    Question q1("Hangi dil C++ programlama dilidir?",
        { "A) Python", "B) Java", "C) C++", "D) Ruby" }, 'C');

    Question q2("C++ dilinde 'new' ve 'delete' operatörleri hangi konuyla ilgilidir?",
        { "A) Dosya işlemleri", "B) Bellek yönetimi", "C) Döngüler", "D) String işlemleri" }, 'B');

    Question q3("C++ dilinde 'cout' ifadesi neyi temsil eder?",
        { "A) Karakter dizisi çıkışı", "B) Giriş işlemi", "C) Ekran çıkışı", "D) Mantıksal işlemler" }, 'C');

    quiz.addQuestion(q1);
    quiz.addQuestion(q2);
    quiz.addQuestion(q3);

    quiz.startQuiz();

    return 0;
}
