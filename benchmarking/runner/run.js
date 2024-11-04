const fs = require('fs');
const cp = require('child_process');

const sleep = (t) => new Promise(r => setTimeout(r, t));

function writeFactor(factor) {
  let content = fs.readFileSync('src/constants.hpp').toString();
  content = content.replace(/FACTOR = .*;/, `FACTOR = ${factor.toFixed(1)};`);
  fs.writeFileSync('src/constants.hpp', content);
}

async function runConfiguration(factor, platform, algorithm) {
  cp.execSync(`just build ${platform} ${algorithm}`);

  let measurements = [];
  for (let i = 0; i < 10; i++) {
    const res = Number(cp.execSync('./build/bin').toString());
    measurements.push(res);
    await sleep(500);
    console.log(factor, platform, algorithm, res);
  }

  fs.writeFileSync(`./results/${factor}-${platform}-${algorithm}.json`, JSON.stringify(measurements));
}

async function main() {
  for (let factor = 1; factor <= 8; factor += 0.5) {
    writeFactor(factor);

    for (const platform of [ 'cpu', 'gpu']) {
      for (const algorithm of ['nearest-neighbor', 'bilinear-interpolation']) {
        await runConfiguration(factor, platform, algorithm);
      }
    }
  }
}

main();

