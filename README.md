# QTodoistFetcher

## Lightweight daemon for fetching tasks from Todoist and sending notifications to Telegram chats.


![alt text](https://img.shields.io/badge/Qt6-6.7.3-blue?style=flat-square&logo=qt) 
![alt text](https://img.shields.io/badge/compatible%20-linux-blue?style=flat-square&logo=linux)
![alt text](https://img.shields.io/badge/compatible%20-windows-blue?style=flat-square)



 ![alt text](https://img.shields.io/badge/Todoist%20app-grey?style=for-the-badge&logo=todoist)
 ![alt text](https://img.shields.io/badge/Telegram%20API-grey?style=for-the-badge&logo=telegram)



 --------------------------------


### ✨ Features

- 🔄 Automatic task fetching from Todoist
- 📱 Notification delivery to Telegram chats
- ⚙️ Flexible configuration via settings file
- 🐧 Cross-platform compatibility (Linux, Windows)
- 🚀 Lightweight daemon with minimal resource usage
- 🛡️ Reliable API error handling


### 🚀 Requirements

- Qt 6.7.3 or higher
- C++ compiler with C++17 support
- HTTP libraries (included with Qt)


### 🔧 Configuration

Edit the `settings.ini` file:

```ini
[todoist]
api_token=your_todoist_api_token_here
project_id=your_project_id_here

[telegram]
bot_token=your_telegram_bot_token_here
chat_id=your_telegram_chat_id_here

[settings]
poll_interval=300000  # Polling interval in milliseconds
```

## 🎯 Usage

```bash
./QTodoistFetcher
```

The application will run as a daemon and automatically poll the Todoist API at the configured interval, sending notifications about new tasks to Telegram.



