from PIL import Image

# gifName = input('Gif: ')
gifName = 'Texture/ladja.gif'
# rotation = input('Rotation: ')
rotation = 280

SCALE = 20

def getFrames(gif):
    try:
        frames = []
        i = 0
        while True:
            gif.seek(i)
            frame = gif.copy()
            if i == 0: 
                palette = frame.getpalette()
            else:
                frame.putpalette(palette)
            frames.append(frame)
            i += 1
    except EOFError:
        return frames

def makeTransparent(frame):
    frame = frame.convert('RGBA')
    data = frame.getdata()
    newData = []
    newData = []
    for item in data:
        if item[0] == 255 and item[1] == 255 and item[2] == 255:
            newData.append((255, 255, 255, 0))
        else:
            newData.append(item)
    frame.putdata(newData)
    return frame

try:
    gif = Image.open(gifName)
except Exception as e:
    print(f'Cant open {gifName}: {e}')
    quit()


frames = getFrames(gif)
w, h = frames[0].width * SCALE, frames[0].height * SCALE
dest = Image.new(mode='RGBA', size=(w + len(frames) * SCALE, h + len(frames) * SCALE) )

for i in range(len(frames)):
    f = frames[i]
    f = makeTransparent(f)
    f = f.resize((w, h)).rotate(rotation)
    for offset in range(SCALE):
        destR = (int(dest.width/2 - w/2), int((dest.height - i*SCALE) - offset - h))
        dest.paste(f, destR, f)

dest.show()