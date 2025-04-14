export enum Objection {
  /**
  * By default, enum are integers 0, 1, 2, ...
  * However, we can also give them string values
  */
  ARGUMENTATIVE = 'argumentative',
  COMPOUND = 'compound',
  HEARSAY = 'hearsay',
  LEADING = 'leading',
  NON_RESPONSIVE = 'non-responsive',
  RELEVANCE = 'relevance',
  SPECULATION = 'speculation',
}

export enum ExaminationType {
  /**
    * It is also possible to specify a "start" number.
    *
    * Below would assign CROSS = 1, DIRECT = 2, the next
    * would be 3, etc.
    */
  CROSS = 1,
  DIRECT,
}

// Helper function - feel free to remove / modify.
function isArgumentative(question: string) {
  return !question.endsWith('?');
}

function getCount(str: string, key: string): number {
  let count = 0;
  while (str.indexOf(key) !== -1) {
    str = str.replace(key, '');
    count++;
  }
  return count;
}

function hasCommon(str1, str2) {
  const clean = (s) =>
    s
      .toLowerCase()
      .replace(/[^a-z0-9\s]/g, '')
      .split(/\s+/)
      .filter(Boolean);

  const words1 = new Set(clean(str1));
  const words2 = clean(str2);

  for (const word of words2) {
    if (words1.has(word)) {
      return true;
    }
  }
  return false;
}

/**
 * Feel free to modify the function below as you see fit,
 * so long as you satisfy the specification.
 */
export function listObjections(
  question: string,
  testimony: string,
  examinationType: ExaminationType
): Set<Objection> {
  // TODO: error handling
  if (question === '') {
    throw new Error('Question is empty');
  }
  if (testimony === '') {
    throw new Error('testimony is empty');
  }
  // Convert given question and testimony to lowercase
  question = question.toLowerCase();
  testimony = testimony.toLowerCase();

  const objections = new Set<Objection>();

  if (examinationType === ExaminationType.CROSS) {
    if (isArgumentative(question)) {
      objections.add(Objection.ARGUMENTATIVE);
    }
    if (question.indexOf('think') !== -1) {
      objections.add(Objection.SPECULATION);
    }
  }

  if (getCount(question, '?') > 1) {
    objections.add(Objection.COMPOUND);
  }

  if ((
    getCount(testimony, 'heard from') + getCount(testimony, 'told me')
  ) > 0) {
    objections.add(Objection.HEARSAY);
  }
  if (examinationType === ExaminationType.DIRECT) {
    if ((
      question.startsWith('why did you') ||
      question.startsWith('do you agree') ||
      question.endsWith('right?') ||
      question.endsWith('correct?')
    )) {
      objections.add(Objection.LEADING);
    }
    if (testimony.indexOf('think') !== -1) {
      objections.add(Objection.SPECULATION);
    }
  }
  if (!hasCommon(testimony, question)) {
    objections.add(Objection.NON_RESPONSIVE);
  }
  if ((3 * question.length) < testimony.length) {
    objections.add(Objection.RELEVANCE);
  }

  // TODO

  return objections;
}
