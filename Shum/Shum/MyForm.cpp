#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <clocale>
#include <filesystem>
#include <direct.h>
#include <Windows.h>
#include <vector>
#include <cstdint>
#include <fstream>

using namespace std;
const long SAMPLE_RATE = 44100;  // Частота дискретизации
const long DURATION = 5;         // Продолжительность звука (в секундах)
const long SIZEE = SAMPLE_RATE * DURATION;
char pathe1[MAX_PATH]; // Для путя

float randomFloat()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 3.0f - 1.0f;
}

// Функция для генерации розового шума
std::vector<sf::Int16> generatePinkNoise(unsigned int sampleCount)
{
    std::vector<sf::Int16> pinkNoise(sampleCount, 0);

    const int numFilters = 90; // Количество фильтров
    std::vector<float> filterValues(numFilters, 5.0f);

    // Создаем фильтры
    std::vector<std::vector<float>> filters(numFilters, std::vector<float>(sampleCount, 0.5f));
    for (int i = 0; i < numFilters; ++i)
    {
        for (unsigned int j = 0; j < sampleCount; ++j)
        {
            filters[i][j] = randomFloat();
        }
    }

    // Фильтрация белого шума
    for (unsigned int i = 0; i < sampleCount; ++i)
    {
        float whiteNoise = randomFloat();

        for (int j = 0; j < numFilters; ++j)
        {
            filterValues[j] += (whiteNoise - filters[j][i]);
            whiteNoise = filters[j][i];
        }

        float pinkSample = 0.0f;
        for (int j = 0; j < numFilters; ++j)
        {
            pinkSample += filterValues[j];
        }

        pinkNoise[i] = static_cast<sf::Int16>(pinkSample * 8192); // Масштабируем значения
    }

    return pinkNoise;
}

int main() {
    _getcwd(pathe1, MAX_PATH);
    std::string exep(pathe1);
    setlocale(LC_ALL, "ru");

    int mecto = 2;

  
    //////////////////////////Белый
    // Создаем генератор случайных чисел
    std::random_device rd1;
    std::mt19937 gen1(rd1());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    // Создаем буфер для звука с установленной частотой дискретизации
    sf::SoundBuffer buffer1;
    buffer1.loadFromSamples(nullptr, 0, 1, SAMPLE_RATE); // 1 канал, частота дискретизации

    // Вычисляем количество сэмплов на основе частоты дискретизации и продолжительности
    int numSamples1 = SAMPLE_RATE * DURATION;
    std::vector<sf::Int16> samples1(numSamples1);

    // Заполняем буфер случайными значениями для создания белого шума
    for (int i = 0; i < numSamples1; i++) {
        sf::Int16 sampleValue = static_cast<sf::Int16>(dist(gen1) * 32767); // Преобразование в 16-битное целое число
        samples1[i] = sampleValue;
    }
    buffer1.loadFromSamples(samples1.data(), numSamples1, 1, SAMPLE_RATE);


    // Создаем объект звука и воспроизводим белый шум
    sf::Sound sound(buffer1);
    sound.setLoop(true);
    ///////////////////////////
    /////////////////////Розовы
    

    const unsigned int sampleRate = 44100; // Частота дискретизации
    const unsigned int durationSeconds = 5; // Продолжительность звука (5 секунд)
    const unsigned int sampleCount = sampleRate * durationSeconds;

    // Генерируем розовый шум
    std::vector<sf::Int16> pinkNoise = generatePinkNoise(sampleCount);

    // Создаем звуковой буфер и загружаем в него аудиоданные
    sf::SoundBuffer buffer2;
    buffer2.loadFromSamples(pinkNoise.data(), sampleCount, 1, sampleRate);

    // Создаем звуковой буфер и загружаем в него аудиоданные

    sf::Sound sound2(buffer2);









    /////////////
    ////////////////
    /////////////////brown

    sf::SoundBuffer buffer3;
    sf::Sound sound3;
    sound3.setLoop(true);
    // Создаем буфер для аудио
    std::vector<sf::Int16> audioData2(SIZEE);

    // Устанавливаем начальное зерно для генератора случайных чисел
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Генерируем коричневый шум
    sf::Int16 lastValue = 0;
    for (unsigned int i = 0; i < SIZEE; ++i)
    {
        // Генерируем случайное значение
        sf::Int16 randomValue = static_cast<sf::Int16>(std::rand() % 65536 - 32768);

        // Применяем фильтр для создания коричневого шума
        lastValue = static_cast<sf::Int16>(0.02 * randomValue + 0.98 * lastValue);

        // Записываем значение в аудио-буфер
        audioData2[i] = lastValue;
    }

    // Загружаем данные в буфер аудио
    if (!buffer3.loadFromSamples(audioData2.data(), SIZEE, 1, SAMPLE_RATE))
    {
        return 1;
    }

    // Устанавливаем буфер для звука и воспроизводим его
    sound3.setBuffer(buffer3);

    ////////////////////////

    sf::RenderWindow window(sf::VideoMode(1200, 800), "Shum");
    /////////////////////////////////

    sf::Texture bufi;
    if (!bufi.loadFromFile(exep + "\\IMG\\walp.png")) {

    }
    sf::Sprite walpe(bufi);

    sf::Texture but_pla;
    if (!but_pla.loadFromFile(exep + "\\IMG\\but_play.png")) {
        
    }
    sf::Sprite button_play(but_pla);
    button_play.setPosition(210, 123);

    sf::Texture but_st;
    if (!but_st.loadFromFile(exep + "\\IMG\\but_stop.png")) {

    }
    sf::Sprite button_stop(but_st);
    button_stop.setPosition(511, 123);
    ////
    sf::Texture but_pla2;
    if (!but_pla2.loadFromFile(exep + "\\IMG\\but_play.png")) {

    }
    sf::Sprite button_play2(but_pla2);
    button_play2.setPosition(210, 323);

    sf::Texture but_st2;
    if (!but_st2.loadFromFile(exep + "\\IMG\\but_stop.png")) {

    }
    sf::Sprite button_stop2(but_st2);
    button_stop2.setPosition(511, 323);
    ////
    sf::Texture but_pla3;
    if (!but_pla3.loadFromFile(exep + "\\IMG\\but_play.png")) {

    }
    sf::Sprite button_play3(but_pla3);
    button_play3.setPosition(210, 523);

    sf::Texture but_st3;
    if (!but_st3.loadFromFile(exep + "\\IMG\\but_stop.png")) {

    }
    sf::Sprite button_stop3(but_st3);
    button_stop3.setPosition(511, 523);
    /////////////
    //Ползунок
    sf::CircleShape slider(20); // Ползунок
    slider.setFillColor(sf::Color::Blue);
    slider.setPosition(1000, 400); // Установите начальные координаты ползунка
    bool isDragging = false;

    //Сам бар
    sf::RectangleShape sliderBar(sf::Vector2f(20, 250)); // Шкала
    sliderBar.setFillColor(sf::Color::Red);
    sliderBar.setPosition(1010, 410);
    int levs = 100;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Обработка нажатия клавиши пробел
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Получение позиции клика
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                    // Проверка, был ли клик на спрайте
                    if (button_play.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                        // Если клик был на спрайте, выводим сообщение в консоль
                        if (mecto != 0)
                        {
                            std::cout << "БЕЛЫЙ ПЛЕЙ" << std::endl;
                            mecto--;
                            sound.play();
                        }
                        else {
                            cout << "Максимально 2 звука!" << endl;
                        }
                    }
                    if (button_stop.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                        // Если клик был на спрайте, выводим сообщение в консоль

                        std::cout << "БЕЛЫЙ СТОП" << std::endl;
                        mecto++;
                        sound.pause();

                    }
                    if (button_play2.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                        // Если клик был на спрайте, выводим сообщение в консоль
                        if (mecto != 0)
                        {
                            sound2.play();
                            mecto--;
                            std::cout << "РОЗОВЫЙ ПЛЕЙ" << std::endl;
                        }
                        else {
                            cout << "Максимально 2 звука!" << endl;
                        }
                    }
                    if (button_stop2.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                        // Если клик был на спрайте, выводим сообщение в консоль

                        sound2.pause();
                        mecto++;
                        std::cout << "РОЗОВЫЙ СТОП" << std::endl;

                    }
                    if (button_play3.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                        // Если клик был на спрайте, выводим сообщение в консоль
                        if (mecto != 0)
                        {
                            sound3.play();
                            mecto--;
                            std::cout << "Коричней ПЛЕЙ" << std::endl;
                        }
                        else {
                            cout << "Максимально 2 звука!" << endl;
                        }
                    }
                    if (button_stop3.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                        // Если клик был на спрайте, выводим сообщение в консоль
                        sound3.pause();
                        mecto++;
                        std::cout << "Коричней СТОП" << std::endl;

                    }
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::FloatRect sliderBounds = slider.getGlobalBounds();

                    if (sliderBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        isDragging = true;
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isDragging = false;
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                if (isDragging) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    float newY = static_cast<float>(mousePos.y);

                    // Ограничьте движение ползунка в пределах окна
                    if (newY < 400) newY = 400;
                    if (newY > 650) newY = 650;
                    levs = 650 - newY;
                    slider.setPosition(1000, newY);
                }
            }
        }
        sound.setVolume(levs / 3);
        sound2.setVolume(levs / 3);
        sound3.setVolume(levs / 3);
        window.clear();
        window.draw(walpe);
        window.draw(button_play);
        window.draw(button_stop);
        window.draw(button_play2);
        window.draw(button_stop2);
        window.draw(button_play3);
        window.draw(button_stop3);
        window.draw(sliderBar);
        window.draw(slider);
        window.display();
    }

}
