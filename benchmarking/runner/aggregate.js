const fs = require('fs');

function toCSV(items) {
  const header = Object.keys(items[0])
  return [
    header.join(','),
    ...items.map(i => header.map(k => i[k]).join(',')),
  ].join('\n');
}

function aggregate(algorithm) {
  const results = [];

  for (let factor = 1; factor <= 8; factor += 0.5) {
    const result = { factor };
    results.push(result);

    for (const platform of ['cpu', 'gpu']) {
      const data = JSON.parse(fs.readFileSync(`./data/raw/${factor}-${platform}-${algorithm}.json`));
      const avg = data.reduce((a, b) => a + b, 0) / data.length;
      result[platform] = avg;
    }
  }

  fs.writeFileSync(`./data/clean/${algorithm}.csv`, toCSV(results));
}

for (const algorithm of ['nearest-neighbor', 'bilinear-interpolation']) {
  aggregate(algorithm);
}
