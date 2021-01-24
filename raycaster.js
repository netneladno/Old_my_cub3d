/**
 * Javasript adaptation of famous : https://lodev.org/cgtutor/raycasting.html
 */

// TODO: find a way to remove the globals
const SCREEN_HEIGHT = 512
const SCREEN_WIDTH = 384
const MOVE_SPEED = (1 / 60) * 3
const ROT_SPEED = (1 / 60) * 6

const worldMap = [
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
  [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
  [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
  [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
  [1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1],
  [1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
  [1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1],
  [1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
  [1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1],
  [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
  [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
  [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
  [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
  [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
  [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
  [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
  [1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
  [1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
  [1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
  [1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
  [1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
  [1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
  [1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
]

const mapWidth = worldMap.length
const mapHeight = worldMap[0].length

let rc = {
  initCanvas () {
    this.canvas = document.createElement('canvas')
    this.ctx = this.canvas.getContext('2d')

    this.canvas.width = SCREEN_WIDTH
    this.canvas.height = SCREEN_HEIGHT

    document.body.appendChild(this.canvas)
  },
  controls (e) {
    let oldDirX
    let oldPlaneX

    switch (e.keyCode) {
      // left
      case 37:
        // We shoudl rotate the direction vector, as well as the camera
        // as we're working with vectors, lets make use of the rotation matrix
        // https://en.wikipedia.org/wiki/Rotation_matrix#Common_rotations
        oldDirX = this.dirX
        oldPlaneX = this.planeX
        this.dirX = this.dirX * Math.cos(ROT_SPEED) - this.dirY * Math.sin(ROT_SPEED)
        this.dirY = oldDirX * Math.sin(ROT_SPEED) + this.dirY * Math.cos(ROT_SPEED)
        this.planeX = this.planeX * Math.cos(ROT_SPEED) - this.planeY * Math.sin(ROT_SPEED)
        this.planeY = oldPlaneX * Math.sin(ROT_SPEED) + this.planeY * Math.cos(ROT_SPEED)
        break
        // top
      case 38:
        // let's move forward friend, if no wall in front obviously
        if (!worldMap[this.int(this.posX + this.dirX * MOVE_SPEED)][this.int(this.posY)]) this.posX += this.dirX * MOVE_SPEED
        if (!worldMap[this.int(this.posX)][this.int(this.posY + this.dirY * MOVE_SPEED)]) this.posY += this.dirY * MOVE_SPEED
        break
        // right
      case 39:
        oldDirX = this.dirX
        oldPlaneX = this.planeX
        this.dirX = this.dirX * Math.cos(-ROT_SPEED) - this.dirY * Math.sin(-ROT_SPEED)
        this.dirY = oldDirX * Math.sin(-ROT_SPEED) + this.dirY * Math.cos(-ROT_SPEED)
        this.planeX = this.planeX * Math.cos(-ROT_SPEED) - this.planeY * Math.sin(-ROT_SPEED)
        this.planeY = oldPlaneX * Math.sin(-ROT_SPEED) + this.planeY * Math.cos(-ROT_SPEED)
        break
        // bottom
      case 40:
        if (!worldMap[this.int(this.posX - this.dirX * MOVE_SPEED)][this.int(this.posY)]) this.posX -= this.dirX * MOVE_SPEED
        if (!worldMap[this.int(this.posX)][this.int(this.posY - this.dirY * MOVE_SPEED)]) this.posY -= this.dirY * MOVE_SPEED
        break
      default:
			  console.log('please use the arrow keys to move on the map')
        break
    }
  },
  setListeners () {
    let controls = this.controls.bind(this)
    document.addEventListener('keydown', controls)
  },
  initValues () {
    // initial values
    // player position
    this.posX = mapWidth / 2
    this.posY = mapHeight / 2

    // direction vector
    // relative to position vector coordinates
    this.dirX = -1
    this.dirY = 0

    // camera plane
    // just a line actually, relative to dir and pos vector.
    this.planeX = 0
    this.planeY = 0.66
  },
  draw () {
    this.clearScreen()

    // drawing loop : for each x pixel column
    for (let x = 0; x < SCREEN_WIDTH; x++) {
    // calculate position and direction
    // -1 to 1 real values. x coordinate of the ray in camera plane
      let cameraX = 2 * x / SCREEN_WIDTH - 1
      let rayDirX = this.dirX + this.planeX * cameraX
      let rayDirY = this.dirY + this.planeY * cameraX

      // which box of the map we're in
      let mapX = this.int(this.posX)
      let mapY = this.int(this.posY)

      // need ot calculate the length of the ray.
      // using pythagoras theorem
      let sideDistX
      let sideDistY

      let perpWallDist

      // the steps to advance the ray depend on the direction vector
      // (where the camera looks)
      let stepX
      let stepY

      // was there a wall hit
      let hit = false

      // On whihc side ? NS / EW ?
      let side

      // how much should the ray be scaled to reach the next
      // square's border
      /**
                 *         y=1
                 *  *********** ***
                 *            *  /
                 *            * / <-  y delta
                 *            °/
                 *   *********
                 *         y=0
                 *
                 *  Considering that the distance can be thought of the hypothenus
                 *  of a right triangle, the formulas leverge pythagorean theorem.
                 *  demonstration here:
                 *  https://gamedev.stackexchange.com/questions/45013/raycasting-tutorial-vector-math-question
                 *
                 *  will jump one square each turn of the loop
                 */
      let deltaDistX = Math.sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
      let deltaDistY = Math.sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))

      if (rayDirX < 0) {
        stepX = -1

        // sideDistX is the distance from the ray startingPosition, to the first
        // side to the left
        sideDistX = (this.posX - mapX) * deltaDistX
      } else {
      // sideDistX is the distance from the ray startingPosition, to the first
      // side to the right
        stepX = 1
        sideDistX = (mapX + 1 - this.posX) * deltaDistX
      }

      if (rayDirY < 0) {
        stepY = -1
        sideDistY = (this.posY - mapY) * deltaDistY
      } else {
        stepY = 1
        sideDistY = (mapY + 1 - this.posY) * deltaDistY
      }
      // perform the DDA
      while (!hit) {
      // make the ray jump to the next closest square
      // eiter horizontally or vertically
        if (sideDistX < sideDistY) {
          sideDistX += deltaDistX
          mapX += stepX
          side = 0 // EW
        } else {
          sideDistY += deltaDistY
          mapY += stepY
          side = 1
        }
        // wall collision detection
        if (worldMap[mapX][mapY] > 0) hit = true
      }

      // Now we calculate the distance from the camera to the wall
      // in order to knwo how tall we should draw it on screen

      // side wall
      if (side === 0) {
        perpWallDist = (mapX - this.posX + (1 - stepX) / 2) / rayDirX
      } else {
      // top or bottom wall
        perpWallDist = (mapY - this.posY + (1 - stepY) / 2) / rayDirY
      }
      let lineHeight = this.int(SCREEN_HEIGHT / perpWallDist)
      let drawStart = this.int(-lineHeight / 2 + SCREEN_HEIGHT / 2)
      let drawEnd = this.int(lineHeight / 2 + SCREEN_HEIGHT / 2)

      // basic collision check
      if (drawStart < 0) drawStart = 0
      if (drawEnd > SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1

      // set color
      let color
      switch (worldMap[mapX][mapY]) {
        case 1:
          color = 'red'
          break
        case 2:
          color = 'green'
          break
        case 3:
          color = 'blue'
          break
        case 4:
          color = 'orange'
          break
        case 5:
          color = 'black'
          break
        default:
          color = 'yellow'
          break
      }
      // draw the line
      this.verLine(x, drawStart, drawEnd, color)
    }

    // recurse
    window.requestAnimationFrame(() => this.draw())
  },
  int (number) {
    return Math.round(number)
  },
  /** verLine draws a vertical line */
  verLine (x, y1, y2, color) {
    this.ctx.beginPath()
    this.ctx.moveTo(x, y1)
    this.ctx.lineTo(x, y2)
    this.ctx.strokeStyle = color
    this.ctx.stroke()
  },
  clearScreen () {
    this.ctx.clearRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)
  },
  main () {
    this.initCanvas()
    this.initValues()
    // start the game loop
    this.draw()
    this.setListeners()
  }
}

rc.main()

/** animations */
let bounce = (startX, startY, color) => {
  let currentX = startX
  let currentY = startY
  let limitX = worldMap.length
  let direction
  return function () {
    // clear previous
    worldMap[currentX][currentY] = 0

    // Wall collisions. -2 because -1 is a wall
    if ((currentX + 1) === (limitX - 2)) {
      direction = 'back'
    }
    if (currentX + 1 <= 2) {
      direction = 'forward'
    }
    // draw
    direction === 'forward' ? ++currentX : --currentX
    worldMap[currentX][currentY] = color
    console.log('curentx', currentX)
  }
}

// animation
let animate = bounce(13, 13, 5)
let animation = setInterval(animate, 1000)