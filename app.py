from flask import Flask, render_template, request
import time

app = Flask(__name__)

@app.route('/')
def index():
    # Read initial bot messages from output.txt
    bot_messages = read_bot_messages()
    user_inputs = read_user_inputs()
    return render_template('index.html', bot_messages=bot_messages, user_inputs=user_inputs)

@app.route('/send', methods=['POST'])
def send():
    # Get user input from the form
    user_input = request.form['user_input']

    # Write user input to input.txt
    write_user_input(user_input)

    # Wait for bot response
    while True:
        time.sleep(1)  # Wait for 1 second

        # Check if new bot message is available
        bot_messages = read_bot_messages()
        if len(bot_messages) > 0:
            break

    user_inputs = read_user_inputs()

    return render_template('index.html', bot_messages=bot_messages, user_inputs=user_inputs)

def read_bot_messages():
    with open('output.txt', 'r') as file:
        messages = file.readlines()
    return [message.strip() for message in messages]

def read_user_inputs():
    with open('input.txt', 'r') as file:
        inputs = file.readlines()
    return [input.strip() for input in inputs]

def write_user_input(user_input):
    with open('input.txt', 'a') as file:
        file.write(user_input + '\n')

if __name__ == '__main__':
    app.run()
