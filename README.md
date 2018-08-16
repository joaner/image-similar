# image-similar (work in processing)
Compare two images of different size are similar

## Usage

```bash
$ ./image-similar test/chrome_48.png test/chrome_32.png
$ echo $?
```

if images are similar, return code is `200`, or else return `201`.

## Install

Required gd-2.2.5
