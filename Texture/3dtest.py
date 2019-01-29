from PIL import Image
import imageio

# gifName = input('Gif: ')
gifName = 'Texture/ladja.gif'
try:
    gif = Image.open(gifName)
except Exception as e:
    print(f'Cant open {gifName}: {e}')
    quit()

rotateGif = input('Rotation gif [Y/n]: ')
if rotateGif.lower() == ('' or 'y' or 'yes' or '1'):
    rotateGif = True
else:
    rotateGif = False
    try:
        rotation = int(input('Rotation (0-360): '))
    except:
        print('Cant parse rotation')

SCALE = input('Scale gif [20]: ')
if SCALE.lower() == (''):
    SCALE = 20
else:
    try:
        SCALE = int(SCALE)
    except:
        print('Cant parse scale')

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

def render(frames, rotation):
    w, h = frames[0].width * SCALE, frames[0].height * SCALE
    dest = Image.new(mode='RGBA', size=(w + len(frames) * SCALE, h + len(frames) * SCALE) )
    for i in range(len(frames)):
        f = frames[i]
        f = makeTransparent(f)
        f = f.resize((w, h)).rotate(rotation)
        for offset in range(SCALE):
            destR = (int(dest.width/2 - w/2), int((dest.height - i*SCALE) - offset - h))
            dest.paste(f, destR, f)

    return dest

frames = getFrames(gif)

if rotateGif:
    gifFrames = []
    for rotation in range(360):
        frame = render(frames, rotation)
        frame.save('/tmp/tmp.png')
        gifFrames.append(imageio.imread('/tmp/tmp.png'))
        print(f'Progress {rotation}/360 ({str(rotation*100/360)[:4]}%)')
    
    destf = gifName.replace('.', '') + '_rotation.gif'
    imageio.mimsave(destf, gifFrames)
    print( f'Saving to {destf}' )
else:
    render(frames, rotation).show()