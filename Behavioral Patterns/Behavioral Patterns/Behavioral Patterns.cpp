#include <iostream>
#include <string>
#include <vector>
using namespace std;
// Получатель действий (компьютерная система)
class ComputerSystem {
public:
    void openFile(const string& file) { cout << "Открываем файл: " << file << endl; }
    void shutdown() { cout << "Выключаем компьютер" << endl; }
    void launchBrowser() { cout << "Запускаем браузер" << endl; }
};

// Интерфейс команды
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;  // Для отмены (опционально)
};

// Конкретные команды
class OpenFileCommand : public Command {
private:
    ComputerSystem* system;
    string fileName;
public:
    OpenFileCommand(ComputerSystem* s, const string& fn) : system(s), fileName(fn) {}
    void execute() override { system->openFile(fileName); }
    void undo() override { cout << "Закрываем файл: " << fileName << endl; }
};

class ShutdownCommand : public Command {
private:
    ComputerSystem* system;
public:
    ShutdownCommand(ComputerSystem* s) : system(s) {}
    void execute() override { system->shutdown(); }
    void undo() override { cout << "Отмена: Включаем компьютер обратно" << endl; }  // Шутка, но в реальности может быть reboot
};

class LaunchBrowserCommand : public Command {
private:
    ComputerSystem* system;
public:
    LaunchBrowserCommand(ComputerSystem* s) : system(s) {}
    void execute() override { system->launchBrowser(); }
    void undo() override { cout << "Закрываем браузер" << endl; }
};

// Вызывающий (пульт или кнопка)
class RemoteControl {
private:
    vector<Command*> commands;  // Очередь команд
public:
    void addCommand(Command* cmd) { commands.push_back(cmd); }
    void pressButton() {  // Нажимаем кнопку — выполняем все
        for (auto cmd : commands) {
            cmd->execute();
        }
    }
    void undoLast() {  // Отмена последней
        if (!commands.empty()) {
            commands.back()->undo();
            commands.pop_back();
        }
    }
};

int main()
{
    setlocale(0, "");
    ComputerSystem system;

    // Настраиваем команды
    Command* openCmd = new OpenFileCommand(&system, "document.txt");
    Command* shutdownCmd = new ShutdownCommand(&system);
    Command* browserCmd = new LaunchBrowserCommand(&system);

    RemoteControl remote;
    remote.addCommand(openCmd);
    remote.addCommand(browserCmd);
    remote.addCommand(shutdownCmd);

    remote.pressButton();  // Вывод: Открываем файл: document.txt
    //        Запускаем браузер
    //        Выключаем компьютер

    remote.undoLast();  // Вывод: Отмена: Включаем компьютер обратно

    delete openCmd;
    delete shutdownCmd;
    delete browserCmd;
}

